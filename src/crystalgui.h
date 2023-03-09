/*******************************************************************************************
*
*   Crystal GUI - A Crystal-Clear Modern-Looking GUI library for raylib.
*
*   DESCRIPTION:
*
*   Crystal GUI is based on raylib but also available as a standalone library,
*   as long as input and drawing functions are provided. This library also has a
*   built-in support for raygui-based programs, Just rename raylib.h to crystalgui.h!
*
*   WARNING: MORE DESCRIPTION TO BE ADDED.
*   WARNING: RAYGUI SUPPORT IS NOT YET AVAILABLE.
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
*******************************************************************************************/

#ifndef CRYSTALGUI_H
#define CRYSTALGUI_H 

#if !defined(CRYSTALGUI_STANDALONE)
    #include "raylib.h"
#endif

#define CRYSTALGUI_VERSION "3.2"

// Function specifiers in case library is build/used as a shared library (Windows)
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #if defined(__TINYC__)
            #define __declspec(x) __attribute__((x))
        #endif
        #define CRYSTALGUIAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define CRYSTALGUIAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#endif

#ifndef CRYSTALGUIAPI
    #define CRYSTALGUIAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------

#if !defined(CRYSTALGUI_MAX_TRACELOG_MSG_LENGTH)
    #define CRYSTALGUI_MAX_TRACELOG_MSG_LENGTH 128     // Max length of one trace-log message
#endif

// Allow custom memory allocators
#ifndef CRYSTALGUI_MALLOC
    #define CRYSTALGUI_MALLOC(sz)       malloc(sz)
#endif
#ifndef CRYSTALGUI_CALLOC
    #define CRYSTALGUI_CALLOC(n,sz)     calloc(n,sz)
#endif
#ifndef CRYSTALGUI_FREE
    #define CRYSTALGUI_FREE(p)          free(p)
#endif

#ifdef CRYSTALGUI_ALLOW_SHADER_LOGS
    #define DISABLE_TRACELOG
    #define ENABLE_TRACELOG
#else
    #define DISABLE_TRACELOG            SetTraceLogCallback(cguiNoTraceLog)
    #define ENABLE_TRACELOG             SetTraceLogCallback(cguiDefaultTraceLog)
#endif

#ifndef TRANSITION_SPEED
    #define TRANSITION_SPEED            10.0f
#endif

//----------------------------------------------------------------------------------
// Types and Structures Definition
// NOTE: Some types are required for CRYSTALGUI_STANDALONE usage
//----------------------------------------------------------------------------------

#if defined(CRYSTALGUI_STANDALONE)
    #ifndef __cplusplus
        // Boolean type
        #if !(defined(false) || defined(true) || defined(bool))
            typedef enum { false, true } bool;
        #endif
    #endif

    // Vector2 type
    typedef struct Vector2 {
        float x;
        float y;
    } Vector2;

    // Vector3 type                 // -- ConvertHSVtoRGB(), ConvertRGBtoHSV()
    typedef struct Vector3 {
        float x;
        float y;
        float z;
    } Vector3;

    // Color type, RGBA (32bit)
    typedef struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } Color;

    // Rectangle type
    typedef struct Rectangle {
        float x;
        float y;
        float width;
        float height;
    } Rectangle;

    // TODO: Texture2D type is very coupled to raylib, required by Font type
    // It should be redesigned to be provided by user
    typedef struct Texture2D {
        unsigned int id;        // OpenGL texture id
        int width;              // Texture base width
        int height;             // Texture base height
        int mipmaps;            // Mipmap levels, 1 by default
        int format;             // Data format (PixelFormat type)
    } Texture2D;

    // Image, pixel data stored in CPU memory (RAM)
    typedef struct Image {
        void *data;             // Image raw data
        int width;              // Image base width
        int height;             // Image base height
        int mipmaps;            // Mipmap levels, 1 by default
        int format;             // Data format (PixelFormat type)
    } Image;

    // GlyphInfo, font characters glyphs info
    typedef struct GlyphInfo {
        int value;              // Character value (Unicode)
        int offsetX;            // Character offset X when drawing
        int offsetY;            // Character offset Y when drawing
        int advanceX;           // Character advance position X
        Image image;            // Character image data
    } GlyphInfo;

    // TODO: Font type is very coupled to raylib, mostly required by GuiLoadStyle()
    // It should be redesigned to be provided by user
    typedef struct Font {
        int baseSize;           // Base size (default chars height)
        int glyphCount;         // Number of glyph characters
        int glyphPadding;       // Padding around the glyph characters
        Texture2D texture;      // Texture atlas containing the glyphs
        Rectangle *recs;        // Rectangles in texture for the glyphs
        GlyphInfo *glyphs;      // Glyphs info data
    } Font;
#endif

// CguiIcon, icons are textures
typedef struct CguiIcon {
    Texture texture;
    const char *name;
} CguiIcon;

//----------------------------------------------------------------------------------
// Enumeration definition
//----------------------------------------------------------------------------------

// Gui control state
typedef enum {
    CRYSTALGUI_STATE_NORMAL = 0,
    CRYSTALGUI_STATE_FOCUSED,
    CRYSTALGUI_STATE_PRESSED,
    CRYSTALGUI_STATE_ACTIVE,
    CRYSTALGUI_STATE_DISABLED,
} CguiState;

//----------------------------------------------------------------------------------
// Cgui Function Types
//----------------------------------------------------------------------------------
// It is recommended to not alter the members that start from two underscores (__)

typedef struct CguiButtonDef {
    Rectangle bounds;
    char *text;
    float __timer;
} CguiButtonDef;

typedef struct CguiDropDownButtonDef {
    Rectangle bounds;
    char **entries;
    int entriesCount;
    int selectedEntry;
    int maxEntriesShown;
    float __timer;
    float __openTimer;
    bool __dropdownActive;
} CguiDropDownButtonDef;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Crystal GUI core functions
//----------------------------------------------------------------------------------

CRYSTALGUIAPI void CguiLoad(void);                            // Load the Cgui resources (must be called before using other functions)
CRYSTALGUIAPI void CguiUnload(void);                          // Unload the Cgui resources (must be called before closing the window)
CRYSTALGUIAPI void CguiBeginBackground(void);                 // Begin drawing into the background. To make it blur behind the Cgui!
CRYSTALGUIAPI void CguiEndBackground(void);                   // End the drawing, this function will immediately process the blur.
CRYSTALGUIAPI void CguiDraw(void);                            // Draw the Cgui from the background buffer
CRYSTALGUIAPI void CguiUpdate(void);                          // This will update the global variables like resoluion, etc. (Internally called)
CRYSTALGUIAPI void CguiShaderUpdate(float *res);              // Update the shader properties like resolution, etc. (Internally called)

CRYSTALGUIAPI void CguiNoTraceLog(int logType, const char *text, ...); // TraceLog that doesn't print anything, useful to not log something
CRYSTALGUIAPI void CguiTraceLog(const char *text, ...);                // Logger used in Cgui functions
CRYSTALGUIAPI Color CguiGetColor(int state);                           // Get the color depending on the state and ratio of old to new, ratio goes from 0.0f to 1.0f
CRYSTALGUIAPI float CguiClamp(float value, float min, float max);      // Clamp value between min amd max
CRYSTALGUIAPI void CguiDrawRectangle(Rectangle bounds, Color tint);    // Draw shader processed rectangle
CRYSTALGUIAPI void CguiDrawText(const char *text, Rectangle bounds);   // Draw text with drop-down shadow

//----------------------------------------------------------------------------------
// Cgui functions
//----------------------------------------------------------------------------------

CRYSTALGUIAPI bool CguiButton(CguiButtonDef *button); // Cgui button, returns true when clicked
CRYSTALGUIAPI int CguiDropDownButton(CguiDropDownButtonDef *ddbutton); // Cgui drop down button, returns clicked entry

//----------------------------------------------------------------------------------
// set/get functions
//----------------------------------------------------------------------------------

CRYSTALGUIAPI void CguiSetDefaultTraceLog(TraceLogCallback callback);
CRYSTALGUIAPI TraceLogCallback CguiGetDefaultTraceLog(void);
CRYSTALGUIAPI void CguiSetNoTraceLog(TraceLogCallback callback);
CRYSTALGUIAPI TraceLogCallback CguiGetNoTraceLog(void);
CRYSTALGUIAPI void CguiSetMouseButton(int mouseButton);
CRYSTALGUIAPI int CguiGetMouseButton(void);

CRYSTALGUIAPI void CguiSetFont(Font font);
CRYSTALGUIAPI Font CguiGetFont(void);
CRYSTALGUIAPI void CguiSetFontSize(float fontSize);
CRYSTALGUIAPI float CguiGetFontSize(void);
CRYSTALGUIAPI void CguiSetFontSpacing(float spacing);
CRYSTALGUIAPI float CguiGetFontSpacing(void);
CRYSTALGUIAPI void CguiSetFontShadowBlurRadius(float blurRadius);
CRYSTALGUIAPI float CguiGetFontShadowBlurRadius(void);
CRYSTALGUIAPI void CguiSetFontShadowOffset(Vector2 offset);
CRYSTALGUIAPI Vector2 CguiGetFontShadowOffset(void);
CRYSTALGUIAPI void CguiSetFontShadowColor(Color color);
CRYSTALGUIAPI Color CguiGetFontShadowColor(void);

CRYSTALGUIAPI void CguiSetShadowColor(Color color);
CRYSTALGUIAPI Color CguiGetShadowColor(void);
CRYSTALGUIAPI void CguiSetAccentColor(Color color);
CRYSTALGUIAPI Color CguiGetAccentColor(void);
CRYSTALGUIAPI void CguiSetDisabledColor(Color color);
CRYSTALGUIAPI Color CguiGetDisabledColor(void);
CRYSTALGUIAPI void CguiSetBackgroundColor(Color color);
CRYSTALGUIAPI Color CguiGetBackgroundColor(void);
CRYSTALGUIAPI void CguiSetForegroundColor(Color color);
CRYSTALGUIAPI Color CguiGetForegroundColor(void);
CRYSTALGUIAPI void CguiSetFocusedFade(Vector3 fade);
CRYSTALGUIAPI Vector3 CguiGetFocusedFade(void);
CRYSTALGUIAPI void CguiSetPressedFade(Vector3 fade);
CRYSTALGUIAPI Vector3 CguiGetPressedFade(void);

//----------------------------------------------------------------------------------
// Shader set/get functions
//----------------------------------------------------------------------------------

CRYSTALGUIAPI void CguiSetBlurRadius(float value);
CRYSTALGUIAPI float CguiGetBlurRadius(void);
CRYSTALGUIAPI void CguiSetBlurQuality(float value);
CRYSTALGUIAPI float CguiGetBlurQuality(void);
CRYSTALGUIAPI void CguiSetRoundness(float value);
CRYSTALGUIAPI float CguiGetRoundness(void);
CRYSTALGUIAPI void CguiSetShadowRadius(float value);
CRYSTALGUIAPI float CguiGetShadowRadius(void);
CRYSTALGUIAPI void CguiSetShadowSize(float value);
CRYSTALGUIAPI float CguiGetShadowSize(void);
CRYSTALGUIAPI void CguiSetShadowOffset(Vector2 offset);
CRYSTALGUIAPI Vector2 CguiGetShadowOffset(void);

#if defined(__cplusplus)
}            // Prevents name mangling of functions
#endif

// RAYGUI SUPPORT IS NOT YET AVAILABLE
// raygui-support mode for raygui-based programs
#if defined(RAYGUI_IMPLEMENTATION)

// This header uses custom implementation of raygui as a compatibility feature
//#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define CRYSTALGUI_IMPLEMENTATION

/***********************************************************************************
*
*   SOME IMPLEMENTATIONS ARE DIRECTLY TAKEN FROM RAYGUI SO THOSE COPYRIGHT NOTICE ARE INCLUDED
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
***********************************************************************************/

#endif // RAYGUI_IMPLEMENTATION

/***********************************************************************************
*
*   CRYSTALGUI IMPLEMENTATION
*
***********************************************************************************/

#if defined(CRYSTALGUI_IMPLEMENTATION)

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// NOTE: MSVC C++ compiler does not support compound literals (C99 feature)
// Plain structures in C++ (without constructors) can be initialized with { }
#ifdef __cplusplus
    #define CRYSTALGUI_CLITERAL(name) name
#else
    #define CRYSTALGUI_CLITERAL(name) (name)
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------

static bool cguiLoaded = false;               // Prevent functions from using unloaded resources
static float cguiScreenResolution[2] = { 0 }; // Screen resolution for shaders and buffer
static bool cguiActivateBuffer = false;       // When true, Cgui functions will draw on the buffer
static CguiIcon cguiIcons[256] = { 0 };       // Each icon texture size is 128x128
static int cguiGlobalState = 0;               // Default Cgui state if this value is 0

static TraceLogCallback cguiDefaultTraceLog = NULL; // NULL to log using raylib's TraceLog
static TraceLogCallback cguiNoTraceLog = NULL;      // Prevent logs whenever shader value is set
static int cguiMouseButton = 0;               // Main mouse button clicks

static Font cguiFont = { 0 };                 // Font to be used in Cgui
static float cguiFontSize = 0.0f;             // Font size of the Cgui
static float cguiFontSpacing = 0.0f;          // Font spacing of the Cgui
static float cguiFontShadowBlurRadius = 0.0f; // Font blur intensity. This feature is not in use for now
static Vector2 cguiFontShadowOffset = { 0 };  // Font blurred shadow offset. This feature is not in use for now
static Color cguiFontShadowColor = { 0 };     // Font blurred shadow color. This feature is not in use for now

static Color cguiShadowColor = { 0 };         // Drop down shadow color
static Color cguiAccentColor = { 0 };         // Main Cgui color
static Color cguiDisabledColor = { 0 };       // Inactive/Disabled color
static Color cguiForegroundColor = { 0 };     // Foreground color (Text color for example)
static Color cguiBackgroundColor = { 0 };     // Background color (Button color in normal state for example)
static Vector3 cguiFocusedFade = { 0 };       // Cgui hsv multiplied modification when the mouse is on top of a Cgui component
static Vector3 cguiPressedFade = { 0 };       // Cgui hsv multiplied modification when the Cgui mouse button is pressed

static Shader cguiBlurShader = { 0 };         // Blur the background for cool effects
static Shader cguiShadowShader = { 0 };       // Fancy shadows for buttons
static Shader cguiRectangleShader = { 0 };    // Rounded rectangle

//----------------------------------------------------------------------------------
// Buffer RenderTexture
//----------------------------------------------------------------------------------

static RenderTexture2D cguiBackgroundBuffer1 = { 0 };
static RenderTexture2D cguiBackgroundBuffer2 = { 0 };
static RenderTexture2D cguiBackgroundBuffer3 = { 0 };
static RenderTexture2D cguiFontBlurBuffer = { 0 };

//----------------------------------------------------------------------------------
// Shader values
//----------------------------------------------------------------------------------

static float cguiBlurRadius = { 0 };
static float cguiBlurQuality = { 0 };
static float cguiRoundness = { 0 };
static float cguiShadowRadius = { 0 };
static float cguiShadowSize = { 0 };
static float cguiShadowOffset[2] = { 0 };

//----------------------------------------------------------------------------------
// Shader Locations
//----------------------------------------------------------------------------------

int cguiBlurShaderResolutionLoc;
int cguiBlurShaderBlurRadiusLoc;

int cguiShadowShaderRectangleLoc;
int cguiShadowShaderRoundnessLoc;
int cguiShadowShaderShadowRadiusLoc;
int cguiShadowShaderShadowSizeLoc;
int cguiShadowShaderShadowColorLoc;
int cguiShadowShaderShadowOffsetLoc;

int cguiRectangleShaderResolutionLoc;
int cguiRectangleShaderRectangleLoc;
int cguiRectangleShaderRoundnessLoc;
int cguiRectangleShaderRectangleTintLoc;

//----------------------------------------------------------------------------------
// Shader codes
//----------------------------------------------------------------------------------

static char cguiBlurShaderCode[] = ""
    // Note: I am not specifying any version of the shader since I am not certain
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"

    "uniform sampler2D texture0;\n"
    "uniform vec2 u_resolution;\n"

    // Custom uniforms
    "uniform float u_blurRadius;\n"
    // Quality is fixed inside the shader so a reload is required to change the quality
    "const float c_blurQuality = %f;\n"

    "void main()\n"
    "{\n"
        // The magic number here is Tau / 4 (or Pi / 2)
        "\tfloat blurRadius = u_blurRadius / c_blurQuality * 1.570796327;\n"
        "\tvec4 finalColor = vec4(0.);\n"

        "\tfor (float a = -c_blurQuality; a <= c_blurQuality; a++)\n"
            "\t\tfor (float b = -c_blurQuality; b <= c_blurQuality; b++)\n"
                "\t\t\tfinalColor += texture2D(texture0, (gl_FragCoord.xy + vec2(a * blurRadius, b * blurRadius)) / u_resolution);\n"
        "\tfinalColor /= 4. * c_blurQuality * c_blurQuality + 4. * c_blurQuality + 1.;\n"

        "\tgl_FragColor = finalColor;\n"
    "}\n";

static char shadowShaderCode[] = ""
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"

    // Custom uniforms
    "uniform vec4 u_rectangle;\n"
    "uniform float u_roundness;\n"
    "uniform float u_shadowRadius;\n"
    "uniform float u_shadowSize;\n"
    "uniform vec4 u_shadowColor;\n"
    "uniform vec2 u_shadowOffset;\n"

    // The documentation of how this function works is provided by this link
    // https://iquilezles.org/articles/distfunctions
    "float RBSDF(vec2 centerPosition, vec2 size, float radius)\n"
    "{\n"
        "\tif (min(size.x, size.y) < radius)\n"
            "\t\tradius = min(size.x, size.y);\n"
        "\treturn length(max(abs(centerPosition) - size + radius, 0.)) - radius;\n"
    "}\n"

    "void main()\n"
    "{\n"
        "\tvec2 size = u_rectangle.zw / 2.;\n"
        "\tvec2 position = gl_FragCoord.xy - u_rectangle.xy - size;\n"
        "\tfloat rectangleRBSDF = smoothstep(0.01, 0., RBSDF(position, size, u_roundness));\n"
        "\tfloat shadowRBSDF = 1. + rectangleRBSDF - smoothstep(0., u_shadowRadius, RBSDF(position - u_shadowOffset, size + u_shadowSize, u_roundness));\n"
        "\tgl_FragColor = u_shadowColor * shadowRBSDF;\n"
    "}\n";

static char rectangleShaderCode[] = ""
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"

    "uniform sampler2D texture0;\n"
    "uniform vec2 u_resolution;\n"

    "uniform vec4 u_rectangle;\n"
    "uniform float u_roundness;\n"
    "uniform vec4 u_rectangleTint;\n"

    "float RBSDF(vec2 centerPosition, vec2 size, float radius)\n"
    "{\n"
        "\tif (min(size.x, size.y) < radius)\n"
            "\t\tradius = min(size.x, size.y);\n"
        "\treturn length(max(abs(centerPosition) - size + radius, 0.)) - radius;\n"
    "}\n"

    "void main()\n"
    "{\n"
        "\tvec2 size = u_rectangle.zw / 2.;\n"
        "\tvec2 position = gl_FragCoord.xy - u_rectangle.xy - size;\n"
        "\tfloat rectangleRBSDF = smoothstep(0.01, 0., RBSDF(position, size, u_roundness));\n"
        "\tvec4 bgcolor = vec4(texture2D(texture0, gl_FragCoord.xy / u_resolution).rgb * rectangleRBSDF, rectangleRBSDF);\n"
        "\tvec4 tint = vec4(u_rectangleTint.rgb * u_rectangleTint.a, u_rectangleTint.a);\n"
        "\tgl_FragColor = bgcolor * (1. - tint.a) + tint * rectangleRBSDF;\n"
    "}\n";

//----------------------------------------------------------------------------------
// Internal functions
//----------------------------------------------------------------------------------

int CguiMin(int a, int b)
{
    return (a < b) ? a : b;
}

int CguiMax(int a, int b)
{
    return (a > b) ? a : b;
}

//----------------------------------------------------------------------------------
// Declarations
//----------------------------------------------------------------------------------

// Load the Cgui resources (must be called before using other functions)
void CguiLoad(void)
{
    // Avoid loading resources that are already loaded
    if (cguiLoaded) return;

    // Pre-adjust the resolution
    cguiScreenResolution[0] = (float)GetScreenWidth();
    cguiScreenResolution[1] = (float)GetScreenHeight();

    // Buffer loading
    //------------------------------------------------------------------------------
    cguiBackgroundBuffer1 = LoadRenderTexture((int)cguiScreenResolution[0], (int)cguiScreenResolution[1]);
    cguiBackgroundBuffer2 = LoadRenderTexture((int)cguiScreenResolution[0], (int)cguiScreenResolution[1]);
    cguiBackgroundBuffer3 = LoadRenderTexture((int)cguiScreenResolution[0], (int)cguiScreenResolution[1]);
    cguiFontBlurBuffer = LoadRenderTexture((int)cguiScreenResolution[0], (int)cguiScreenResolution[1]);
    //------------------------------------------------------------------------------

    // Shader loading
    //------------------------------------------------------------------------------
    cguiBlurShader = LoadShaderFromMemory(NULL, TextFormat(cguiBlurShaderCode, 2.5f));
    cguiShadowShader = LoadShaderFromMemory(NULL, TextFormat(shadowShaderCode));
    cguiRectangleShader = LoadShaderFromMemory(NULL, TextFormat(rectangleShaderCode));

    // Shader location is set once
    //------------------------------------------------------------------------------
    cguiBlurShaderResolutionLoc = GetShaderLocation(cguiBlurShader, "u_resolution");
    cguiBlurShaderBlurRadiusLoc = GetShaderLocation(cguiBlurShader, "u_blurRadius");

    cguiShadowShaderRectangleLoc = GetShaderLocation(cguiShadowShader, "u_rectangle");
    cguiShadowShaderRoundnessLoc = GetShaderLocation(cguiShadowShader, "u_roundness");
    cguiShadowShaderShadowRadiusLoc = GetShaderLocation(cguiShadowShader, "u_shadowRadius");
    cguiShadowShaderShadowSizeLoc = GetShaderLocation(cguiShadowShader, "u_shadowSize");
    cguiShadowShaderShadowColorLoc = GetShaderLocation(cguiShadowShader, "u_shadowColor");
    cguiShadowShaderShadowOffsetLoc = GetShaderLocation(cguiShadowShader, "u_shadowOffset");

    cguiRectangleShaderResolutionLoc = GetShaderLocation(cguiRectangleShader, "u_resolution");
    cguiRectangleShaderRectangleLoc = GetShaderLocation(cguiRectangleShader, "u_rectangle");
    cguiRectangleShaderRoundnessLoc = GetShaderLocation(cguiRectangleShader, "u_roundness");
    cguiRectangleShaderRectangleTintLoc = GetShaderLocation(cguiRectangleShader, "u_rectangleTint");
    //------------------------------------------------------------------------------

    cguiLoaded = true;

    // Default initialization
    //------------------------------------------------------------------------------
    cguiDefaultTraceLog = NULL;
    cguiNoTraceLog = (TraceLogCallback)CguiNoTraceLog;
    cguiMouseButton = MOUSE_BUTTON_LEFT;

    cguiFont = GetFontDefault();
    cguiFontSize = 30.0f;
    cguiFontSpacing = 1.0f;
    cguiFontShadowBlurRadius = 1.0f;
    cguiFontShadowOffset = CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 1.0f };

#if defined(CRYSTALGUI_DARK_THEME)
    cguiFontShadowColor = CRYSTALGUI_CLITERAL(Color){ 0, 0, 0, 255 };
    cguiShadowColor = CRYSTALGUI_CLITERAL(Color){ 0, 0, 0, 127 };
    cguiDisabledColor = CRYSTALGUI_CLITERAL(Color){ 127, 127, 127, 255 };
    cguiAccentColor = CRYSTALGUI_CLITERAL(Color){ 0, 170, 255, 255 };
    cguiForegroundColor = CRYSTALGUI_CLITERAL(Color){ 255, 255, 255, 255 };
    cguiBackgroundColor = CRYSTALGUI_CLITERAL(Color){ 49, 51, 56, 192 };
    cguiFocusedFade = CRYSTALGUI_CLITERAL(Vector3){ 0.0f, 0.0f, +0.05f };
    cguiPressedFade = CRYSTALGUI_CLITERAL(Vector3){ 0.0f, 0.0f, -0.05f };
#elif defined(CRYSTALGUI_LIGHT_THEME) || defined(RAYGUI_IMPLEMENTATION)
    cguiFontShadowColor = CRYSTALGUI_CLITERAL(Color){ 0, 0, 0, 255 };
    cguiShadowColor = CRYSTALGUI_CLITERAL(Color){ 51, 51, 51, 127 };
    cguiDisabledColor = CRYSTALGUI_CLITERAL(Color){ 127, 127, 127, 255 };
    cguiAccentColor = CRYSTALGUI_CLITERAL(Color){ 0, 170, 255, 255 };
    cguiForegroundColor = CRYSTALGUI_CLITERAL(Color){ 0, 0, 0, 255 };
    cguiBackgroundColor = CRYSTALGUI_CLITERAL(Color){ 255, 255, 255, 192 };
    cguiFocusedFade = CRYSTALGUI_CLITERAL(Vector3){ 0.0f, 0.0f, 0.0f };
    cguiPressedFade = CRYSTALGUI_CLITERAL(Vector3){ 0.0f, 0.0f, -0.2f };
#else
    cguiFontShadowColor = CRYSTALGUI_CLITERAL(Color){ 0, 0, 0, 255 };
    cguiShadowColor = CRYSTALGUI_CLITERAL(Color){ 127, 127, 127, 255 };
    cguiDisabledColor = CRYSTALGUI_CLITERAL(Color){ 127, 127, 127, 255 };
    cguiAccentColor = CRYSTALGUI_CLITERAL(Color){ 0, 170, 255, 255 };
    cguiForegroundColor = CRYSTALGUI_CLITERAL(Color){ 0, 0, 0, 255 };
    cguiBackgroundColor = CRYSTALGUI_CLITERAL(Color){ 127, 127, 127, 255 };
    cguiFocusedFade = CRYSTALGUI_CLITERAL(Vector3){ 0.0f, 0.0f, 0.01f };
    cguiPressedFade = CRYSTALGUI_CLITERAL(Vector3){ 0.0f, 0.0f, -0.01f };
#endif
    //------------------------------------------------------------------------------

    // Shader default values
    //------------------------------------------------------------------------------
    CguiSetBlurRadius(10.0f);
    //CguiSetBlurQuality(7.5f); // This reloads the shader so it is not required to do so
    CguiSetRoundness(10.0f);
    CguiSetShadowRadius(30.0f);
    CguiSetShadowSize(-10.0f);
    CguiSetShadowOffset(CRYSTALGUI_CLITERAL(Vector2){ 0.0f, -10.0f });

    // Update shader resolution
    CguiShaderUpdate(cguiScreenResolution);
    //------------------------------------------------------------------------------
}

// Unload the Cgui resources (must be called before closing the rectangle)
void CguiUnload(void)
{
    // Prevent unloading before loading
    if (!cguiLoaded) return;

    UnloadShader(cguiBlurShader);
    UnloadShader(cguiShadowShader);
    UnloadShader(cguiRectangleShader);
    UnloadRenderTexture(cguiBackgroundBuffer1);
    UnloadRenderTexture(cguiBackgroundBuffer2);
    UnloadRenderTexture(cguiBackgroundBuffer3);
    UnloadRenderTexture(cguiFontBlurBuffer);

    cguiLoaded = false;
}

// Begin drawing into the background. To make it blur behind the Cgui!
void CguiBeginBackground(void)
{
    // Prevent function usage if resources are not loaded
    if (!cguiLoaded) return;

    CguiUpdate();
    BeginTextureMode(cguiBackgroundBuffer1);
    ClearBackground(BLANK);

    cguiActivateBuffer = true;
}

// End the drawing, this function will process the blur
void CguiEndBackground(void)
{
    // Prevent function usage if resources are not loaded
    if (!cguiLoaded) return;

    EndTextureMode();

    // Blur the background and keep it in cguiBackgroundBuffer2
    BeginTextureMode(cguiBackgroundBuffer2);
        // Note: We are clearing the buffer
        ClearBackground(BLANK);

        BeginShaderMode(cguiBlurShader);
            DrawTexturePro(cguiBackgroundBuffer1.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], -cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
        EndShaderMode();
    EndTextureMode();
}

// Draw the Cgui from background buffer
void CguiDraw(void)
{
    // Prevent function usage if resources are not loaded
    if (!cguiLoaded) return;

    cguiActivateBuffer = false;
    DrawTexturePro(cguiBackgroundBuffer1.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], -cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
    DrawTexturePro(cguiBackgroundBuffer3.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], -cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);

    // Background buffer 3 is a dynamic background buffer so we clear it before it's a mess
    BeginTextureMode(cguiBackgroundBuffer3);
        ClearBackground(BLANK);
    EndTextureMode();
}

// This will update the global variables (Internally called)
void CguiUpdate(void)
{
    // Prevent function usage if resources are not loaded
    if (!cguiLoaded) return;

    if (IsWindowResized())
    {
        // Update resolution
        //--------------------------------------------------------------------------
        cguiScreenResolution[0] = (float)GetScreenWidth();
        cguiScreenResolution[1] = (float)GetScreenHeight();
        CguiShaderUpdate(cguiScreenResolution);
        //--------------------------------------------------------------------------

        // Reload the background buffers
        //--------------------------------------------------------------------------
        UnloadRenderTexture(cguiBackgroundBuffer1);
        UnloadRenderTexture(cguiBackgroundBuffer2);
        UnloadRenderTexture(cguiBackgroundBuffer3);
        UnloadRenderTexture(cguiFontBlurBuffer);

        cguiBackgroundBuffer1 = LoadRenderTexture((int)cguiScreenResolution[0], (int)cguiScreenResolution[1]);
        cguiBackgroundBuffer2 = LoadRenderTexture((int)cguiScreenResolution[0], (int)cguiScreenResolution[1]);
        cguiBackgroundBuffer3 = LoadRenderTexture((int)cguiScreenResolution[0], (int)cguiScreenResolution[1]);
        cguiFontBlurBuffer = LoadRenderTexture((int)cguiScreenResolution[0], (int)cguiScreenResolution[1]);
        //--------------------------------------------------------------------------

        // Clear the background
        //--------------------------------------------------------------------------
        BeginTextureMode(cguiBackgroundBuffer1);
            ClearBackground(BLANK);
        CguiEndBackground();
        BeginTextureMode(cguiBackgroundBuffer2);
            ClearBackground(BLANK);
        CguiEndBackground();
        BeginTextureMode(cguiBackgroundBuffer3);
            ClearBackground(BLANK);
        CguiEndBackground();
        BeginTextureMode(cguiFontBlurBuffer);
            ClearBackground(BLANK);
        CguiEndBackground();
        //--------------------------------------------------------------------------
    }
}

// Update the shader cuiShaderResolution
void CguiShaderUpdate(float *res)
{
    // Prevent function usage if resources are not loaded
    if (!cguiLoaded) return;

    DISABLE_TRACELOG;
    SetShaderValue(cguiBlurShader, cguiBlurShaderResolutionLoc, res, SHADER_UNIFORM_VEC2);
    SetShaderValue(cguiRectangleShader, cguiRectangleShaderResolutionLoc, res, SHADER_UNIFORM_VEC2);
    ENABLE_TRACELOG;
}

// TraceLog that doesn't print anything, useful to not log something
void CguiNoTraceLog(int logType, const char *text, ...)
{
    // Prevent function usage if resources are not loaded
    if (!cguiLoaded) return;

    // Do nothing
}

// Logger used in Cgui functions
void CguiTraceLog(const char *text, ...)
{
    va_list args;
    va_start(args, text);
    char buffer[CRYSTALGUI_MAX_TRACELOG_MSG_LENGTH] = { 0 };

    strcpy(buffer, "CGUI: ");

    strcat(buffer, text);
    strcat(buffer, "\n");
    vprintf(buffer, args);
    fflush(stdout);

    va_end(args);
}

// Get the color depending on the state
Color CguiGetColor(int state)
{
    Vector3 hsvColor = ColorToHSV(cguiBackgroundColor);

    switch (state)
    {
    case CRYSTALGUI_STATE_NORMAL:
        return cguiBackgroundColor;
    case CRYSTALGUI_STATE_FOCUSED:
        return ColorAlpha(ColorFromHSV(hsvColor.x + cguiFocusedFade.x, hsvColor.y + cguiFocusedFade.y, hsvColor.z + cguiFocusedFade.z), cguiBackgroundColor.a / 255.0f);
    case CRYSTALGUI_STATE_PRESSED:
        return ColorAlpha(ColorFromHSV(hsvColor.x + cguiPressedFade.x, hsvColor.y + cguiPressedFade.y, hsvColor.z + cguiPressedFade.z), cguiBackgroundColor.a / 255.0f);
    case CRYSTALGUI_STATE_ACTIVE:
        return cguiAccentColor;
    case CRYSTALGUI_STATE_DISABLED:
        return cguiDisabledColor;
    }
}

// Clamp value between min amd max
float CguiClamp(float value, float min, float max)
{
    if (min > max)
    {
        float tmp = max;
        max = min;
        min = tmp;
    }

    return fmaxf(fminf(value, max), min);
}

// SDraw shader processed rectangle
void CguiDrawRectangle(Rectangle bounds, Color tint)
{
    // Prevent function usage if resources are not loaded
    if (!cguiLoaded) return;

    // 4-component array used as vector for rectangle
    float rectangle[4] = { rectangle[0] = bounds.x, rectangle[1] = GetScreenHeight() - bounds.y - bounds.height, rectangle[2] = bounds.width, rectangle[3] = bounds.height };

    // 4-component array used as vector for color
    float color[4] = { color[0] = tint.r / 255.0f, color[1] = tint.g / 255.0f, color[2] = tint.b / 255.0f, color[3] = tint.a / 255.0f };

    // Apply Shader Value
    //------------------------------------------------------------------------------
    DISABLE_TRACELOG;

    // Apply the rectangle
    SetShaderValue(cguiShadowShader, cguiShadowShaderRectangleLoc, rectangle, SHADER_UNIFORM_VEC4);
    SetShaderValue(cguiRectangleShader, cguiRectangleShaderRectangleLoc, rectangle, SHADER_UNIFORM_VEC4);

    // Apply the color
    SetShaderValue(cguiRectangleShader, cguiRectangleShaderRectangleTintLoc, color, SHADER_UNIFORM_VEC4);

    ENABLE_TRACELOG;
    //------------------------------------------------------------------------------

    // Apply shadow shader and rectangle shader on buffer 3
    //------------------------------------------------------------------------------
    BeginTextureMode(cguiBackgroundBuffer3);
        BeginShaderMode(cguiShadowShader);
            DrawRectangleRec(CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], cguiScreenResolution[0] }, BLANK);
        EndShaderMode();
        BeginShaderMode(cguiRectangleShader);
            DrawTexturePro(cguiBackgroundBuffer2.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], -cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
        EndShaderMode();
    EndTextureMode();
    //------------------------------------------------------------------------------
}

// Draw text with drop-down shadow
void CguiDrawText(const char *text, Rectangle bounds)
{
    Vector2 textSize = MeasureTextEx(cguiFont, text, cguiFontSize, cguiFontSpacing);
    Vector2 textPosition = { bounds.x + (bounds.width - textSize.x) / 2.0f, bounds.y + (bounds.height - textSize.y) / 2.0f };
    textPosition.x += cguiFontShadowOffset.x;
    textPosition.y += cguiFontShadowOffset.y;
    float shaderBlurRadius = cguiBlurRadius;

    // Put font in blur buffer
    //------------------------------------------------------------------------------
    BeginTextureMode(cguiFontBlurBuffer);
        // Erase contents before use
        ClearBackground(BLANK);
        // Font will not escape the bounds
        BeginScissorMode(bounds.x, bounds.y, bounds.width, bounds.height);
            DrawTextEx(cguiFont, text, textPosition, cguiFontSize, cguiFontSpacing, cguiFontShadowColor);
        EndScissorMode();
    EndTextureMode();
    //------------------------------------------------------------------------------

    // Apply shadow shader and blur the font on buffer 3
    //------------------------------------------------------------------------------
    BeginTextureMode(cguiBackgroundBuffer3);

        // Temporarily set font blur radius and restore afterwards
        DISABLE_TRACELOG;
        CguiSetBlurRadius(cguiFontShadowBlurRadius);
        BeginShaderMode(cguiBlurShader);
            DrawTexturePro(cguiFontBlurBuffer.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], -cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, cguiScreenResolution[0], cguiScreenResolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
        EndShaderMode();
        CguiSetBlurRadius(shaderBlurRadius);
        ENABLE_TRACELOG;

        textPosition.x -= CguiGetFontShadowOffset().x;
        textPosition.y -= CguiGetFontShadowOffset().y;

        // Font will not escape the bounds
        BeginScissorMode(bounds.x, bounds.y, bounds.width, bounds.height);
            DrawTextEx(cguiFont, text, textPosition, cguiFontSize, cguiFontSpacing, cguiForegroundColor);
        EndScissorMode();
    EndTextureMode();
    //------------------------------------------------------------------------------
}

//----------------------------------------------------------------------------------
// Cgui functions
//----------------------------------------------------------------------------------

// Cgui button, returns true when clicked
bool CguiButton(CguiButtonDef *button)
{
    if (!cguiLoaded) return false;

    Color color;
    int state = 0;
    bool result = false;

    float shaderColor[4] = { cguiShadowColor.r / 255.0f, cguiShadowColor.g / 255.0f, cguiShadowColor.b / 255.0f };

    // Update state
    //------------------------------------------------------------------------------
    if (cguiGlobalState == 0)
    {
        state = CRYSTALGUI_STATE_NORMAL;
        if (CheckCollisionPointRec(GetMousePosition(), button->bounds))
        {
            button->__timer = CguiClamp(button->__timer + TRANSITION_SPEED * GetFrameTime(), 0.0f, 1.0f);
            state = CRYSTALGUI_STATE_FOCUSED;
            if (IsMouseButtonDown(cguiMouseButton))
                state = CRYSTALGUI_STATE_PRESSED;
            if (IsMouseButtonReleased(cguiMouseButton))
                result = true;
        }
        else button->__timer = CguiClamp(button->__timer - TRANSITION_SPEED * GetFrameTime(), 0.0f, 1.0f);
    }
    else state = cguiGlobalState - 1;
    color = CguiGetColor(state);
    shaderColor[3] = cguiShadowColor.a / 255.0f * button->__timer;
    //------------------------------------------------------------------------------

    // Draw Cgui
    //------------------------------------------------------------------------------
    DISABLE_TRACELOG;
    SetShaderValue(cguiShadowShader, cguiShadowShaderShadowColorLoc, shaderColor, SHADER_UNIFORM_VEC4);
    ENABLE_TRACELOG;

    CguiDrawRectangle(button->bounds, color);
    CguiDrawText(button->text, button->bounds);
    //------------------------------------------------------------------------------

    return result;
}

// Cgui drop down button, returns clicked entry
int CguiDropDownButton(CguiDropDownButtonDef *ddbutton)
{
    if (!cguiLoaded) return -1;
    int state = 0;
    bool pressed = false;

    // Update state
    //------------------------------------------------------------------------------
    if (cguiGlobalState == 0)
    {
        state = CRYSTALGUI_STATE_NORMAL;
        if (CheckCollisionPointRec(GetMousePosition(), ddbutton->bounds))
        {
            ddbutton->__timer = CguiClamp(ddbutton->__timer + TRANSITION_SPEED * GetFrameTime(), 0.0f, 1.0f);
            state = CRYSTALGUI_STATE_FOCUSED;
            if (IsMouseButtonDown(cguiMouseButton))
                state = CRYSTALGUI_STATE_PRESSED;
            if (IsMouseButtonReleased(cguiMouseButton))
                pressed = true;
        }
        else ddbutton->__timer = CguiClamp(ddbutton->__timer - TRANSITION_SPEED * GetFrameTime(), 0.0f, 1.0f);
    }
    //------------------------------------------------------------------------------

    // Update 
    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------

    // Draw Cgui
    //------------------------------------------------------------------------------
    //------------------------------------------------------------------------------
}

//----------------------------------------------------------------------------------
// set/get functions
//----------------------------------------------------------------------------------

void CguiSetDefaultTraceLog(TraceLogCallback callback)
{
    cguiDefaultTraceLog = callback;
}

TraceLogCallback CguiGetDefaultTraceLog(void)
{
    return cguiDefaultTraceLog;
}

void CguiSetNoTraceLog(TraceLogCallback callback)
{
    cguiNoTraceLog = callback;
}

TraceLogCallback CguiGetNoTraceLog(void)
{
    return cguiNoTraceLog;
}

void CguiSetMouseButton(int mouseButton)
{
    cguiMouseButton = mouseButton;
}

int CguiGetMouseButton(void)
{
    return cguiMouseButton;
}

void CguiSetFont(Font font)
{
    cguiFont = font;
}

Font CguiGetFont(void)
{
    return cguiFont;
}

void CguiSetFontSize(float fontSize)
{
    cguiFontSize = fontSize;
}

float CguiGetFontSize(void)
{
    return cguiFontSize;
}

void CguiSetFontSpacing(float spacing)
{
    cguiFontSpacing = spacing;
}

float CguiGetFontSpacing(void)
{
    return cguiFontSpacing;
}

void CguiSetFontShadowBlurRadius(float blurRadius)
{
    cguiFontShadowBlurRadius = blurRadius;
}

float CguiGetFontShadowBlurRadius(void)
{
    return cguiFontShadowBlurRadius;
}

void CguiSetFontShadowOffset(Vector2 offset)
{
    cguiFontShadowOffset = offset;
}

Vector2 CguiGetFontShadowOffset(void)
{
    return cguiFontShadowOffset;
}

void CguiSetFontShadowColor(Color color)
{
    cguiFontShadowColor = color;
}

Color CguiGetFontShadowColor(void)
{
    return cguiFontShadowColor;
}

void CguiSetShadowColor(Color color)
{
    cguiShadowColor = color;
}

Color CguiGetShadowColor(void)
{
    return cguiShadowColor;
}

void CguiSetAccentColor(Color color)
{
    cguiAccentColor = color;
}

Color CguiGetAccentColor(void)
{
    return cguiAccentColor;
}

void CguiSetDisabledColor(Color color)
{
    cguiDisabledColor = color;
}

Color CguiGetDisabledColor(void)
{
    return cguiDisabledColor;
}

void CguiSetBackgroundColor(Color color)
{
    cguiBackgroundColor = color;
}

Color CguiGetBackgroundColor(void)
{
    return cguiBackgroundColor;
}

void CguiSetForegroundColor(Color color)
{
    cguiForegroundColor = color;
}

Color CguiGetForegroundColor(void)
{
    return cguiForegroundColor;
}

void CguiSetFocusedFade(Vector3 fade)
{
    cguiFocusedFade = fade;
}

Vector3 CguiGetFocusedFade(void)
{
    return cguiFocusedFade;
}

void CguiSetPressedFade(Vector3 fade)
{
    cguiPressedFade = fade;
}

Vector3 CguiGetPressedFade(void)
{
    return cguiPressedFade;
}

//----------------------------------------------------------------------------------
// Shader getters and setters (not always is simple)
//----------------------------------------------------------------------------------

void CguiSetBlurRadius(float value)
{
    if (!cguiLoaded) return;
    cguiBlurRadius = value;
    SetShaderValue(cguiBlurShader, cguiBlurShaderBlurRadiusLoc, &cguiBlurRadius, SHADER_UNIFORM_FLOAT);
}

float CguiGetBlurRadius(void)
{
    return cguiBlurRadius;
}

void CguiSetBlurQuality(float value)
{
    if (!cguiLoaded) return;
    cguiBlurQuality = value;

    // Requires reload of shader because quality is a constant
    UnloadShader(cguiBlurShader);
    cguiBlurShader = LoadShaderFromMemory(NULL, TextFormat(cguiBlurShaderCode, cguiBlurQuality));
    CguiShaderUpdate(cguiScreenResolution);

    // Reset the other uniforms
    CguiSetBlurRadius(cguiBlurRadius);
}

float CguiGetBlurQuality(void)
{
    return cguiBlurQuality;
}

void CguiSetRoundness(float value)
{
    if (!cguiLoaded) return;
    cguiRoundness = value;
    SetShaderValue(cguiShadowShader, cguiShadowShaderRoundnessLoc, &cguiRoundness, SHADER_UNIFORM_FLOAT);
    SetShaderValue(cguiRectangleShader, cguiRectangleShaderRoundnessLoc, &cguiRoundness, SHADER_UNIFORM_FLOAT);
}

float CguiGetRoundness(void)
{
    return cguiRoundness;
}

void CguiSetShadowRadius(float value)
{
    if (!cguiLoaded) return;
    cguiShadowRadius = value;
    SetShaderValue(cguiShadowShader, cguiShadowShaderShadowRadiusLoc, &cguiShadowRadius, SHADER_UNIFORM_FLOAT);
}

float CguiGetShadowRadius(void)
{
    return cguiShadowRadius;
}

void CguiSetShadowSize(float value)
{
    if (!cguiLoaded) return;
    cguiShadowSize = value;
    SetShaderValue(cguiShadowShader, cguiShadowShaderShadowSizeLoc, &cguiShadowSize, SHADER_UNIFORM_FLOAT);
}

float CguiGetShadowSize(void)
{
    return cguiShadowSize;
}

void CguiSetShadowOffset(Vector2 offset)
{
    if (!cguiLoaded) return;
    cguiShadowOffset[0] = offset.x;
    cguiShadowOffset[1] = offset.y;
    SetShaderValue(cguiShadowShader, cguiShadowShaderShadowOffsetLoc, cguiShadowOffset, SHADER_UNIFORM_VEC2);
}

Vector2 CguiGetShadowOffset(void)
{
    return CRYSTALGUI_CLITERAL(Vector2){ cguiShadowOffset[0], cguiShadowOffset[1] };
}

#endif // CRYSTALGUI_IMPLEMENTATION

#endif // CRYSTALGUI_H
