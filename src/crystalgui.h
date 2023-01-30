/*
 * Crystal GUI (crystalgui) is a GUI library built on raylib.
 *
 * This library even provides support for raygui, A simple and easy-to-use
 * immediate-mode gui library
 *
 * Defining "RAYGUI_IMPLEMENTATION" before including this library will cause
 * this library to be used as comparibility mode for raygui. Make sure to
 * load the resources after initializing the window and unload them before
 * closing the window.
 * 
 * The usage of comparibility mode is almost the same as raygui so make sure
 * to read the documentation and examples of those. Those may be provided
 * in this repository.
 *
 * Copyright (c) 2023 Anstro Pleuton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CRYSTALGUI_H
#define CRYSTALGUI_H

// Function specifiers in case library is build/used as a shared library (Windows)
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #define CRYSTALGUIAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define CRYSTALGUIAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#endif

// Function specifiers definition
#ifndef CRYSTALGUIAPI
    #define CRYSTALGUIAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

// Global Crystal Gui core functions
CRYSTALGUIAPI void CrystalGuiLoad(void);   // Call this before using any Crystal Gui functions (Note: Must be called after the window is initialized)
CRYSTALGUIAPI void CrystalGuiUnload(void); // Call this before closing the window
CRYSTALGUIAPI void CrystalGuiBegin(void);  // Begin drawing into the background. To make it blur behind the Gui!
CRYSTALGUIAPI void CrystalGuiEnd(void);    // End the drawing
CRYSTALGUIAPI void CrystalGuiDraw(void);   // Draw the blurred background and gui

#if defined(__cplusplus)
}            // Prevents name mangling of functions
#endif

#ifdef RAYGUI_IMPLEMENTATION

// This header uses custom implementation of raygui as a compatibility feature
//#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#endif // RAYGUI_IMPLEMENTATION

#if defined(CRYSTALGUI_IMPLEMENTATION)

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
static Shader blurShader = { 0 };
static Shader shadowShader = { 0 };
static char blurShaderCode[] = ""
    // Note: I am not specifying any version of the shader since I am not certain.
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    ""
    "uniform sampler2D texture0;"
    "uniform vec2 u_resolution;"
    ""
    // Custom uniforms
    "uniform float u_blurRadius;"
    // Quality is fixed inside the shader so a reload is required to change the quality.
    "const float c_blurQuality = %f;"
    ""
    "void main()"
    "{"
    // The magic number here is Tau / 4 (or Pi / 2)
    "    float blurRadius = u_blurRadius / c_blurQuality * 1.570796327;"
    "    vec4 finalColor = vec4(0.);"
    "    for (float a = -c_blurQuality; a <= c_blurQuality; a++)"
    "        for (float b = -c_blurQuality; b <= c_blurQuality; b++)"
    "            finalColor += texture2D(texture0, (gl_FragCoord.xy + vec2(a * blurRadius, b * blurRadius)) / u_resolution);"
    "    finalColor /= 4. * c_blurQuality * c_blurQuality + 4. * c_blurQuality + 1.;"
    ""
    "    gl_FragColor = finalColor;"
    "}"
    "";
static char shadowShaderCode[] = ""
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    ""
    "uniform sampler2D texture0;"
    "uniform vec2 u_resolution;"
    ""
    // Custom uniforms
    "uniform vec4 u_rectangle;"
    "uniform float u_roundness;"
    "uniform float u_shadowRadius;"
    "uniform float u_shadowSize;"
    "uniform vec4 u_shadowColor;"
    "uniform vec2 u_shadowOffset;"
    ""
    // The documentation of how this shader works is provided by this link.
    // https://iquilezles.org/articles/distfunctions
    "float RBSDF(vec2 centerPosition, vec2 size, float radius)"
    "{"
    "    if (min(size.x, size.y) < radius)"
    "        radius = min(size.x, size.y);"
    "    return length(max(abs(centerPosition) - size + radius, 0.)) - radius;"
    "}"
    ""
    "void main()"
    "{"
    "    vec2 size = u_rectangle.zw / 2.;"
    "    vec2 position = gl_FragCoord.xy - u_rectangle.xy - size;"
    "    float rectangleRBSDF = smoothstep(1., 0., RBSDF(position, size, u_roundness));"
    "    float shadowRBSDF = 1. + rectangleRBSDF - smoothstep(0., u_shadowRadius, RBSDF(position - u_shadowOffset, size + u_shadowSize, u_roundness));"
    "    vec4 bgcolor = vec4(texture2D(texture0, gl_FragCoord.xy / u_resolution).rgb * rectangleRBSDF, rectangleRBSDF);"
    "    gl_FragColor = bgcolor + vec4(u_shadowColor * shadowRBSDF);"
    "}"
    "";

void CrystalGuiLoad(void)
{
    blurShader = LoadShaderFromMemory(0, blurShaderCode);
    shadowShader = LoadShaderFromMemory(0, shadowShaderCode);
}

void CrystalGuiUnload(void)
{
    UnloadShader(blurShader);
    UnloadShader(shadowShader);
}

#endif // CRYSTALGUI_IMPLEMENTATION

#endif // CRYSTALGUI_H
