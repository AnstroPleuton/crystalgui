/*******************************************************************************************
*
*   Crystal GUI is a GUI tool built on raylib. This is header-only library.
*   This library also has a built-in support for raygui-based programs.
*
*   USAGE:
*
*   Load the GUI resources using CrystalGuiLoad function after initializing the window.
*   Unload them before closing the window using CrystalGuiUnload function.
*   If choose to use the background blur method,
*       In the game loop, befoer BeginDrawing, use the CrystalGui functions.
*       In the game loop, befoer BeginDrawing, use CrystalGuiBeginBackground and draw all
*         the things that you need to be behind the GUi and to be blurred.
*       Make sure to do CystalGuiEndBackground once you are done drawing.
*       Now in the BeginDrawing, draw the GUI with CrystalGuiDraw function.
*   Else
*       In the game loop, inside BeginDrawing, use the CrystalGui functions.
*       (This is similar to raygui and acts as a built-in support)
*
*   RAYGUI:
*
*   Defining "RAYGUI_IMPLEMENTATION" before including this library will cause
*   this library to be used as comparibility mode for raygui. 
*
*   The usage of comparibility mode is almost the same as raygui so make sure
*   to read the documentation and examples of those. Those may be provided
*   in this repository.
*
*   LICENSE: Unmodified MIT License.
*
*   Copyright (c) 2023 Anstro Pleuton
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

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

//----------------------------------------------------------------------------------
// The GUI draws things on the buffer if the CystalGuiBeginBackground and
// CystalGuiEndBackground functions are used. Begin background function will
// redirect the draws into a background buffer 1 and end drawing will blur the
// background buffer 1 and put it into background buffer 2. If those functions are
// used then CrystalGui will draw things on background buffer 3. And then
// CrystalGuiDraw will draw the contents of the background buffer 3.
// If CystalGuiBeginBackground and CystalGuiEndBackground functions are not used
// the CrystalGui functions will directly draw the GUI instead of redirecting it to
// the background buffers.
//----------------------------------------------------------------------------------

// Global Crystal GUI core functions
CRYSTALGUIAPI void CrystalGuiLoad(void);            // Load the GUI resources (must be called before using other functions)
CRYSTALGUIAPI void CrystalGuiUnload(void);          // Call this before closing the window
CRYSTALGUIAPI void CrystalGuiBeginBackground(void); // Begin drawing into the background. To make it blur behind the GUI!
CRYSTALGUIAPI void CrystalGuiEndBackground(void);   // End the drawing, Make sure to use it after CrystalGuiBeginDrawing
CRYSTALGUIAPI void CrystalGuiDraw(void);            // Draw the GUI from background buffer
CRYSTALGUIAPI void CrystalGuiUpdate(void);          // This will update the global variables (Internally called)

// Font set/get functions
CRYSTALGUIAPI void CrystalGuiSetFont(Font font);    // Set GUI custom font
CRYSTALGUIAPI Font CrystalGuiGetFont(void);         // Get GUI custom font

CRYSTALGUIAPI void CrystalGuiNullLogger(int logType, const char *text, ...); // TraceLog that doesn't print anything, useful to not log something
// CRYSTALGUIAPI void CrystalGui;

#if defined(__cplusplus)
}            // Prevents name mangling of functions
#endif

#ifdef RAYGUI_IMPLEMENTATION

// This header uses custom implementation of raygui as a compatibility feature
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define CRYSTALGUI_IMPLEMENTATION

#endif // RAYGUI_IMPLEMENTATION

#if defined(CRYSTALGUI_IMPLEMENTATION)

#ifdef __cplusplus
    #define CRYSTALGUI_CLITERAL(name) name
#else
    #define CRYSTALGUI_CLITERAL(name) (name)
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
static bool resourceLoaded = false; // Keep track of resources loaded state
static Shader blurShader = { 0 };   // Simple shader used to blur a specific image
static Shader shadowShader = { 0 }; // Not so simple shader used to generate shadow and a rounded rectangle
static float resolution[2] = { 0 }; // Note: This is not Integer because it is intended to be used in the uniforms of the shaders
static bool usedBackground = false; // Determine if the CrystalGui functions should redirect draws to background
static TraceLogCallback defaultLogger = { 0 }; // Default logger used in raylib
static TraceLogCallback nullLogger = { 0 };    // Null logger to not log something
static Font defaultFont = { 0 };    // Default font used in CrystalGui functions

//----------------------------------------------------------------------------------
// Background Buffer RenderTexture
//----------------------------------------------------------------------------------
static RenderTexture2D backgroundBuffer1 = { 0 };
static RenderTexture2D backgroundBuffer2 = { 0 };
static RenderTexture2D backgroundBuffer3 = { 0 };

//----------------------------------------------------------------------------------
// Shader codes
//----------------------------------------------------------------------------------
static char blurShaderCode[] = ""
    // Note: I am not specifying any version of the shader since I am not certain
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"

    "uniform sampler2D texture0;"
    "uniform vec2 u_resolution;"

    // Custom uniforms
    "uniform float u_blurRadius;"
    // Quality is fixed inside the shader so a reload is required to change the quality
    "const float c_blurQuality = %f;"

    "void main()"
    "{"
    // The magic number here is Tau / 4 (or Pi / 2)
       "float blurRadius = u_blurRadius / c_blurQuality * 1.570796327;"
       "vec4 finalColor = vec4(0.);"
       "for (float a = -c_blurQuality; a <= c_blurQuality; a++)"
           "for (float b = -c_blurQuality; b <= c_blurQuality; b++)"
               "finalColor += texture2D(texture0, (gl_FragCoord.xy + vec2(a * blurRadius, b * blurRadius)) / u_resolution);"
       "finalColor /= 4. * c_blurQuality * c_blurQuality + 4. * c_blurQuality + 1.;"

       "gl_FragColor = finalColor;"
    "}";

static char shadowShaderCode[] = ""
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"

    "uniform sampler2D texture0;"
    "uniform vec2 u_resolution;"

    // Custom uniforms
    "uniform vec4 u_rectangle;"
    "uniform float u_roundness;"
    "uniform float u_shadowRadius;"
    "uniform float u_shadowSize;"
    "uniform vec4 u_shadowColor;"
    "uniform vec2 u_shadowOffset;"

    // The documentation of how this function works is provided by this link
    // https://iquilezles.org/articles/distfunctions
    "float RBSDF(vec2 centerPosition, vec2 size, float radius)"
    "{"
       "if (min(size.x, size.y) < radius)"
           "radius = min(size.x, size.y);"
       "return length(max(abs(centerPosition) - size + radius, 0.)) - radius;"
    "}"

    "void main()"
    "{"
       "vec2 size = u_rectangle.zw / 2.;"
       "vec2 position = gl_FragCoord.xy - u_rectangle.xy - size;"
       "float rectangleRBSDF = smoothstep(1., 0., RBSDF(position, size, u_roundness));"
       "float shadowRBSDF = 1. + rectangleRBSDF - smoothstep(0., u_shadowRadius, RBSDF(position - u_shadowOffset, size + u_shadowSize, u_roundness));"
       "vec4 bgcolor = vec4(texture2D(texture0, gl_FragCoord.xy / u_resolution).rgb * rectangleRBSDF, rectangleRBSDF);"
       "gl_FragColor = bgcolor + vec4(u_shadowColor * shadowRBSDF);"
    "}"
    "";

//----------------------------------------------------------------------------------
// Declarations
//----------------------------------------------------------------------------------

void CrystalGuiLoad(void)
{
    // Prevent loading again
    if (resourceLoaded) return;

    // Loading stuff
    //--------------------------------------------------------------------
    blurShader = LoadShaderFromMemory(0, TextFormat(blurShaderCode, 2.5f));
    shadowShader = LoadShaderFromMemory(0, TextFormat(shadowShaderCode));

    backgroundBuffer1 = LoadRenderTexture((int) resolution[0], (int) resolution[1]);
    backgroundBuffer2 = LoadRenderTexture((int) resolution[0], (int) resolution[1]);
    backgroundBuffer3 = LoadRenderTexture((int) resolution[0], (int) resolution[1]);

    defaultLogger = TraceLog;
    nullLogger = CrystalGuiNullLogger;

    defaultFont = GetFontDefault();
    //--------------------------------------------------------------------

    // Shader configurations
    //--------------------------------------------------------------------
    resolution[0] = (float)GetScreenWidth();
    resolution[1] = (float)GetScreenHeight();

    // Set shader resolution
    SetShaderValue(blurShader, GetShaderLocation(blurShader, "u_resolution"), resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(shadowShader, GetShaderLocation(shadowShader, "u_resolution"), resolution, SHADER_UNIFORM_VEC2);
    //--------------------------------------------------------------------
}

void CrystalGuiUnload(void)
{
    // Prevent unloading before loading
    if (!resourceLoaded) return;

    UnloadShader(blurShader);
    UnloadShader(shadowShader);

    UnloadRenderTexture(backgroundBuffer1);
    UnloadRenderTexture(backgroundBuffer2);
    UnloadRenderTexture(backgroundBuffer3);
}

void CrystalGuiBeginBackground(void)
{
    if (!resourceLoaded) return;

    // Update the background buffers (size) before using
    CrystalGuiUpdate();

    BeginTextureMode(backgroundBuffer1);

    // Note: We are clearing the buffer
    ClearBackground(BLANK);

    usedBackground = true;
}

void CrystalGuiEndBackground(void)
{
    if (!resourceLoaded) return;
    EndTextureMode();

    // Blur the background and keep it in swap 2
    BeginTextureMode(backgroundBuffer2);
        BeginShaderMode(blurShader);
            DrawTexturePro(backgroundBuffer1.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], -resolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], resolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
        EndShaderMode();
    EndTextureMode();
}

void CrystalGuiDraw(void)
{
    usedBackground = false;
    DrawTexturePro(backgroundBuffer3.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], -resolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], resolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
}

void CrystalGuiUpdate(void)
{
    if (IsWindowResized())
    {
        // Reload the background buffers
        //--------------------------------------------------------------------
        UnloadRenderTexture(backgroundBuffer1);
        UnloadRenderTexture(backgroundBuffer2);
        UnloadRenderTexture(backgroundBuffer3);

        backgroundBuffer1 = LoadRenderTexture((int) resolution[0], (int) resolution[1]);
        backgroundBuffer2 = LoadRenderTexture((int) resolution[0], (int) resolution[1]);
        backgroundBuffer3 = LoadRenderTexture((int) resolution[0], (int) resolution[1]);
        //--------------------------------------------------------------------

        // Reset the shader resolution
        //--------------------------------------------------------------------
        resolution[0] = (float)GetScreenWidth();
        resolution[1] = (float)GetScreenHeight();

        // Disable logging
        SetTraceLogCallback(nullLogger);

        SetShaderValue(blurShader, GetShaderLocation(blurShader, "u_resolution"), resolution, SHADER_UNIFORM_VEC2);
        SetShaderValue(shadowShader, GetShaderLocation(shadowShader, "u_resolution"), resolution, SHADER_UNIFORM_VEC2);

        // Enable logging
        SetTraceLogCallback(defaultLogger);
        //--------------------------------------------------------------------
    }
}

void CrystalGuiSetFont(Font font)
{
    if (font.texture.id > 0)
    {
        defaultFont = font;
    }
}

Font CrystalGuiGetFont(void)
{
    return defaultFont;
}

void CrystalGuiNullLogger(int logType, const char *text, ...)
{
    // Do nothing
}

#endif // CRYSTALGUI_IMPLEMENTATION

#endif // CRYSTALGUI_H
