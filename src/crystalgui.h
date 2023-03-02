/*******************************************************************************************
*
*   Crystal GUI is a GUI tool built on raylib. This is header-only library.
*   This library also has a built-in support for raygui-based programs.
*
*   USAGE:
*
*   Load the GUI resources using CguiLoad() function after initializing the window.
*   Unload them before closing the window using CguiUnload() function.
*   If choose to use the background blur method,
*       In the game loop, befoer BeginDrawing, use the Cgui functions.
*       In the game loop, befoer BeginDrawing, use CguiBeginBackground(false) and
*         draw all the things that you need to be behind the GUi and to be blurred.
*       Make sure to do CguiEndBackground(true) once you are done drawing.
*       Now in the BeginDrawing, draw the GUI with CguiDraw function.
*   Else
*       In the game loop, inside BeginDrawing, use the Cgui functions.
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
*******************************************************************************************/

#ifndef CRYSTALGUI_H
#define CRYSTALGUI_H

// The version of Crystal GUI is the same as raygui
#define CRYSTALGUI_VERSION "3.2"

#include "raylib.h"
#include <stdbool.h>
#include <stddef.h>

// Function specifiers in case library is build/used as a shared library (Windows)
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #define CRYSTALGUIAPI __declspec(dllexport)          // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define CRYSTALGUIAPI __declspec(dllimport)          // We are using the library as a Win32 shared library (.dll)
    #endif
#endif

// Function specifiers definition
#ifndef CRYSTALGUIAPI
    #define CRYSTALGUIAPI                                    // Functions defined as 'extern' by default (implicit specifiers)
#endif

#if defined(__cplusplus)
extern "C" {                                                 // Prevents name mangling of functions
#endif

// Disable or enable logging in shader
#ifdef CRYSTALGUI_SHADER_LOGS
    #define DISABLE_LOGGER
    #define ENABLE_LOGGER
#else
    #define DISABLE_LOGGER SetTraceLogCallback(nullLogger)
    #define ENABLE_LOGGER SetTraceLogCallback(defaultLogger)
#endif

//----------------------------------------------------------------------------------
// The GUI draws things on the buffer if the CystalGuiBeginBackground and
// CguiEndBackground functions are used. Begin background function will
// redirect the draws into a backgroundBuffer1 and end drawing will blur the
// backgroundBuffer1 and put it into backgroundBuffer2. If those functions are
// used then Cgui will draw things on backgroundBuffer3. And then
// CguiDraw will draw the contents of the backgroundBuffer3.
// If CystalGuiBeginBackground and CguiEndBackground functions are not used
// the Cgui functions will directly draw the GUI instead of redirecting it to
// the background buffers.
//----------------------------------------------------------------------------------

// Global Crystal GUI core functions
CRYSTALGUIAPI void CguiLoad(void);                            // Load the GUI resources (must be called before using other functions)
CRYSTALGUIAPI void CguiUnload(void);                          // Unload the GUI resources (must be called before closing the window)
CRYSTALGUIAPI void CguiBeginBackground(bool skip);            // Begin drawing into the background. To make it blur behind the GUI!
CRYSTALGUIAPI void CguiEndBackground(bool skip);              // End the drawing, this function will process the blur
CRYSTALGUIAPI void CguiDraw(void);                            // Draw the GUI from background buffer
CRYSTALGUIAPI void CguiUpdate(void);                          // This will update the global variables (Internally called)
CRYSTALGUIAPI void CguiShaderUpdate(void);                    // Update the shader resolution

CRYSTALGUIAPI void CguiNullLogger(int logType, const char *text, ...); // TraceLog that doesn't print anything, useful to not log something
CRYSTALGUIAPI void CguiDrawRectangle(Rectangle bounds);                // Draw shader processed rectangle

// GUI Control parameter types
// This is to make the usage of the GUI easier. In between PARAM_START and PARAM_END
// goes parameter, the list of values that the function recieves. And in between
// INTERNAL_START and INTERNAL_END goes the list of variables that the function uses
// internally, do not modify these values. These are NOT shared variables. You can
// define your own way of accessing parameters, the default way is accessing witn
// '<braiable>.param.<parameter>' ex:
// | CguiButtonParam myButton;
// | myButton.param.bounds = (Rectangle){ 20.0f, 20.0f, 200.0f, 40.0f };
// In between PARAM_OPTIONAL_START and PARAM_OPTIONAL_END goes optional parameter.
// You can change it's values if wish.
//----------------------------------------------------------------------------------
#define PARAM_START struct {
#define PARAM_END } param
#define PARAM_OPTIONAL_START struct {
#define PARAM_OPTIONAL_END void *null; } optional
#define INTERNAL_START struct {
#define INTERNAL_END void *null; } internal

typedef struct { PARAM_START Rectangle bounds; const char *text;                                                                                                PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiLabelParam;
typedef struct { PARAM_START Rectangle bounds; const char *text;                                                                                                PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START float timer; INTERNAL_END; } CguiButtonParam;
typedef struct { PARAM_START Rectangle bounds; const char *text;                                                                                                PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiLabelButtonParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; bool active;                                                                                   PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiToggleParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; int active;                                                                                    PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiToggleGroupParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; bool checked;                                                                                  PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiCheckBoxParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; int active;                                                                                    PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiComboBoxParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; int *active; bool editMode;                                                                    PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiDropdownBoxParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; int *value; int minValue; int maxValue; bool editMode;                                         PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiSpinnerParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; int *value; int minValue; int maxValue; bool editMode;                                         PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiValueBoxParam;
typedef struct { PARAM_START Rectangle bounds; char *text; int textSize; bool editMode;                                                                         PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiTextBoxParam;
typedef struct { PARAM_START Rectangle bounds; char *text; int textSize; bool editMode;                                                                         PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiTextBoxMultiParam;
typedef struct { PARAM_START Rectangle bounds; const char *textLeft; const char *textRight; float value; float minValue; float maxValue;                        PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiSliderParam;
typedef struct { PARAM_START Rectangle bounds; const char *textLeft; const char *textRight; float value; float minValue; float maxValue;                        PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiSliderBarParam;
typedef struct { PARAM_START Rectangle bounds; const char *textLeft; const char *textRight; float value; float minValue; float maxValue;                        PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiProgressBarParam;
typedef struct { PARAM_START Rectangle bounds; const char *text;                                                                                                PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiStatusBarParam;
typedef struct { PARAM_START Rectangle bounds; const char *text;                                                                                                PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiDummyRecParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; float spacing; int subdivs;                                                                    PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiGridParam;

typedef struct { PARAM_START Rectangle bounds; const char *text; int *scrollIndex; int active;                                                                  PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiListViewParam;
typedef struct { PARAM_START Rectangle bounds; const char **text; int count; int *focus; int *scrollIndex; int active;                                          PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiListViewExParam;
typedef struct { PARAM_START Rectangle bounds; const char *title; const char *message; const char *buttons;                                                     PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiMessageBoxParam;
typedef struct { PARAM_START Rectangle bounds; const char *title; const char *message; const char *buttons; char *text; int textMaxSize; int *secretViewActive; PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiTextInputBoxParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; Color color;                                                                                   PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiColorPickerParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; Color color;                                                                                   PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiColorPanelParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; float alpha;                                                                                   PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiColorBarAlphaParam;
typedef struct { PARAM_START Rectangle bounds; const char *text; float value;                                                                                   PARAM_END; PARAM_OPTIONAL_START PARAM_OPTIONAL_END; INTERNAL_START INTERNAL_END; } CguiColorBarHueParam;
//----------------------------------------------------------------------------------

// Basic controls set
CRYSTALGUIAPI void CguiLabel(CguiLabelParam *cguiLabelParam);                         // Label control, shows text
CRYSTALGUIAPI bool CguiButton(CguiButtonParam *cguiButtonParam);                      // Button control, returns true when clicked, timer is for shadow control
CRYSTALGUIAPI bool CguiLabelButton(CguiLabelButtonParam *cguiLabelButtonParam);        // Label button control, show true when clicked
CRYSTALGUIAPI bool CguiToggle(CguiToggleParam *cguiToggleParam);                       // Toggle Button control, returns true when active
CRYSTALGUIAPI int CguiToggleGroup(CguiToggleGroupParam *cguiToggleGroupParam);         // Toggle Group control, returns active toggle index
CRYSTALGUIAPI bool CguiCheckBox(CguiCheckBoxParam *cguiCheckBoxParam);                 // Check Box control, returns true when active
CRYSTALGUIAPI int CguiComboBox(CguiComboBoxParam *cguiComboBoxParam);                  // Combo Box control, returns selected item index
CRYSTALGUIAPI bool CguiDropdownBox(CguiDropdownBoxParam *cguiDropdownBoxParam);        // Dropdown Box control, returns selected item
CRYSTALGUIAPI bool CguiSpinner(CguiSpinnerParam *cguiSpinnerParam);                    // Spinner control, returns selected value
CRYSTALGUIAPI bool CguiValueBox(CguiValueBoxParam *cguiValueBoxParam);                 // Value Box control, updates input text with numbers
CRYSTALGUIAPI bool CguiTextBox(CguiTextBoxParam *cguiTextBoxParam);                    // Text Box control, updates input text
CRYSTALGUIAPI bool CguiTextBoxMulti(CguiTextBoxMultiParam *cguiTextBoxMultiParam);     // Text Box control with multiple lines
CRYSTALGUIAPI float CguiSlider(CguiSliderParam *cguiSliderParam);                      // Slider control, returns selected value
CRYSTALGUIAPI float CguiSliderBar(CguiSliderBarParam *cguiSliderBarParam);             // Slider Bar control, returns selected value
CRYSTALGUIAPI float CguiProgressBar(CguiProgressBarParam *cguiProgressBarParam);       // Progress Bar control, shows current progress value
CRYSTALGUIAPI void CguiStatusBar(CguiStatusBarParam *cguiStatusBarParam);              // Status Bar control, shows info text
CRYSTALGUIAPI void CguiDummyRec(CguiDummyRecParam *cguiDummyRecParam);                 // Dummy control for placeholders
CRYSTALGUIAPI Vector2 CguiGrid(CguiGridParam *cguiGridParam);                          // Grid control, returns mouse cell position

// Advance controls set
CRYSTALGUIAPI int CguiListView(CguiListViewParam *cguiListViewParam);                  // List View control, returns selected list item index
CRYSTALGUIAPI int CguiListViewEx(CguiListViewExParam *cguiListViewExParam);            // List View with extended parameters
CRYSTALGUIAPI int CguiMessageBox(CguiMessageBoxParam *cguiMessageBoxParam);            // Message Box control, displays a message
CRYSTALGUIAPI int CguiTextInputBox(CguiTextInputBoxParam *cguiTextInputBoxParam);      // Text Input Box control, ask for text, supports secret
CRYSTALGUIAPI Color CguiColorPicker(CguiColorPickerParam *cguiColorPickerParam);       // Color Picker control (multiple color controls)
CRYSTALGUIAPI Color CguiColorPanel(CguiColorPanelParam *cguiColorPanelParam);          // Color Panel control
CRYSTALGUIAPI float CguiColorBarAlpha(CguiColorBarAlphaParam *cguiColorBarAlphaParam); // Color Bar Alpha control
CRYSTALGUIAPI float CguiColorBarHue(CguiColorBarHueParam *cguiColorBarHueParam);       // Color Bar Hue control

// Tooltips management functions
CRYSTALGUIAPI void GuiEnableTooltip(void);                    // Enable gui tooltips (global state)
CRYSTALGUIAPI void GuiDisableTooltip(void);                   // Disable gui tooltips (global state)
CRYSTALGUIAPI void GuiSetTooltip(const char *tooltip);        // Set tooltip string

// set/get functions
CRYSTALGUIAPI void CguiSetFont(Font font);                    // Set the GUI custom font
CRYSTALGUIAPI Font CguiGetFont(void);                         // Get the GUI custom font
CRYSTALGUIAPI void CguiSetAccentColor(Color color);           // Get the accent colors for the GUI
CRYSTALGUIAPI Color CguiGetAccentColor(void);                 // Get the accent colors for the GUI
CRYSTALGUIAPI void CguiSetBackgroundColor(Color color);       // Get the background colors for the GUI
CRYSTALGUIAPI Color CguiGetBackgroundColor(void);             // Get the background colors for the GUI
CRYSTALGUIAPI void CguiSetForegroundColor(Color color);       // Get the foreground colors for the GUI
CRYSTALGUIAPI Color CguiGetForegroundColor(void);             // Get the foreground colors for the GUI
CRYSTALGUIAPI void CguiSetFontShadowColor(Color color);       // Get the font colors for the GUI
CRYSTALGUIAPI Color CguiGetFontShadowColor(void);             // Get the font colors for the GUI
CRYSTALGUIAPI void CguiSetFontSize(float fontSize);           // Set the GUI custom font size
CRYSTALGUIAPI float CguiGetFontSize(void);                    // Get the GUI Custom font size
CRYSTALGUIAPI void CguiSetFontShadowOffset(Vector2 value);    // Set the offset of shadow from text
CRYSTALGUIAPI Vector2 CguiGetFontShadowOffset(void);          // Get the offset of shadow for text
CRYSTALGUIAPI void CguiSetFontShadowBlurRadius(float offset); // Set the blur radius of shadow for text
CRYSTALGUIAPI float CguiGetFontShadowBlurRadius(void);        // Get the blur radius of shadow for text
CRYSTALGUIAPI void CguiSetMainMouseButton(int button);        // Set the main mouse button for the GUI
CRYSTALGUIAPI int CguiGetMainMouseButton(void);               // Get the main mouse button for the GUIs

// Shader get/set functions
// Blur Radius   - The indensity of blur in shader
// Blur Quality  - The quality of resulting image, higher this value slower the shader
// Roundness     - The rounded corner intensity of GUI
// Shadow Radius - The range of shadow from the window
// Shadow Size   - The size of shadow relative to the window
// Shadow Color  - The color of the shadow
// Shadow Offset - The position of shadow relative to window
// Window Tint   - The color of the window
//----------------------------------------------------------------------------------
CRYSTALGUIAPI float CguiGetBlurRadius(void);
CRYSTALGUIAPI float CguiGetBlurQuality(void);
CRYSTALGUIAPI float CguiGetRoundness(void);
CRYSTALGUIAPI float CguiGetShadowRadius(void);
CRYSTALGUIAPI float CguiGetShadowSize(void);
CRYSTALGUIAPI Color CguiGetShadowColor(void);
CRYSTALGUIAPI Vector2 CguiGetShadowOffset(void);
CRYSTALGUIAPI Color CguiGetWindowTint(void);
CRYSTALGUIAPI void CguiSetBlurRadius(float value);
CRYSTALGUIAPI void CguiSetBlurQuality(float value);
CRYSTALGUIAPI void CguiSetRoundness(float value);
CRYSTALGUIAPI void CguiSetShadowRadius(float value);
CRYSTALGUIAPI void CguiSetShadowSize(float value);
CRYSTALGUIAPI void CguiSetShadowColor(Color color);
CRYSTALGUIAPI void CguiSetShadowOffset(Vector2 offset);
CRYSTALGUIAPI void CguiSetWindowTint(Color color);
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
}            // Prevents name mangling of functions
#endif

// RAYGUI SUPPORT IS NOT YET AVAILABLE
// raygui-support mode for raygui-based programs
#if defined(RAYGUI_IMPLEMENTATION)

// This header uses custom implementation of raygui as a compatibility feature
#undef RAYGUI_IMPLEMENTATION
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

#include <string.h>

#if defined(CRYSTALGUI_IMPLEMENTATION)

#ifdef __cplusplus
    #define CRYSTALGUI_CLITERAL(name) name
#else
    #define CRYSTALGUI_CLITERAL(name) (name)
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
static bool resourceLoaded = false;    // Keep track of resources loaded state
static Shader blurShader = { 0 };      // Simple shader used to blur an image
static Shader shadowShader = { 0 };    // Not so simple shader used to generate shadow
static Shader windowShader = { 0 };    // Again not so simple shader used to draw window with custom background with tint
static float resolution[2] = { 0 };    // Note: This is not Integer because it is intended to be used in the uniforms of the shaders
static bool usedBackground = false;    // Determine if the Cgui functions should redirect draws to background
static TraceLogCallback defaultLogger = TraceLog; // Default logger used in raylib
static TraceLogCallback nullLogger = NULL;        // Null logger to not log something
static Font customFont = { 0 };        // Font used in Cgui functions
static float customFontSize = 0.0f;    // Custom font size for the GUI
static bool skinFrame = false;         // Not always you need to invoke the blur process
static Texture *icons = { 0 };         // Icons are made of textures
static char *iconNames = { 0 };        // Name of each icons
static Color accentColor = { 0 };      // Accent color for the GUI
static Color foregroundColor = { 0 };  // Main foreground color of the GUI
static Color backgroundColor = { 0 };  // Main background color of the GUI
static Color fontShadowColor = { 0 };  // Main font color of the GUI
static Vector2 fontShadowOffset = { 0 };  // Position of the blurred shadow of text
static float fontShadowBlurRadius = 0.0f; // Blur radius for the font
static int mainMouseButton = 0;        // Main mouse button for the GUI

//----------------------------------------------------------------------------------
// Background Buffer RenderTexture
//----------------------------------------------------------------------------------
static RenderTexture2D backgroundBuffer1 = { 0 };
static RenderTexture2D backgroundBuffer2 = { 0 };
static RenderTexture2D backgroundBuffer3 = { 0 };

// Font blur buffer
static RenderTexture2D fontBlurBuffer = { 0 };

//----------------------------------------------------------------------------------
// Shader values
//----------------------------------------------------------------------------------
static float blurRadius = { 0 };
static float blurQuality = { 0 };
static float roundness = { 0 };
static float shadowRadius = { 0 };
static float shadowSize = { 0 };
static float shadowColor[4] = { 0 };
static float shadowOffset[2] = { 0 };
static float windowTint[4] = { 0 };

//----------------------------------------------------------------------------------
// Shader value locations inside shader
//----------------------------------------------------------------------------------
static int blurShaderResLoc = 0;
static int blurRadiusLoc = 0;
static int shadowRoundnessLoc = 0;
static int shadowRectangleLoc = 0;
static int shadowRadiusLoc = 0;
static int shadowSizeLoc = 0;
static int shadowColorLoc = 0;
static int shadowOffsetLoc = 0;
static int windowShaderResLoc = 0;
static int windowRoundnessLoc = 0;
static int windowRectangleLoc = 0;
static int windowTintLoc = 0;

//----------------------------------------------------------------------------------
// Shader codes
//----------------------------------------------------------------------------------
static char blurShaderCode[] = ""
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
       "\tfloat rectangleRBSDF = smoothstep(1., 0., RBSDF(position, size, u_roundness));\n"
       "\tfloat shadowRBSDF = 1. + rectangleRBSDF - smoothstep(0., u_shadowRadius, RBSDF(position - u_shadowOffset, size + u_shadowSize, u_roundness));\n"
       "\tgl_FragColor = u_shadowColor * shadowRBSDF;\n"
    "}\n";

static char windowShaderCode[] = ""
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"

    "uniform sampler2D texture0;\n"
    "uniform vec2 u_resolution;\n"

    "uniform vec4 u_rectangle;\n"
    "uniform float u_roundness;\n"
    "uniform vec4 u_windowTint;\n"

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
       "\tfloat rectangleRBSDF = smoothstep(1., 0., RBSDF(position, size, u_roundness));\n"
       "\tvec4 bgcolor = vec4(texture2D(texture0, gl_FragCoord.xy / u_resolution).rgb * rectangleRBSDF, rectangleRBSDF);\n"
       "\tvec4 tint = vec4(u_windowTint.rgb * u_windowTint.a, u_windowTint.a);\n"
       "\tgl_FragColor = bgcolor * (1. - tint.a) + tint * rectangleRBSDF;\n"
    "}\n";

//----------------------------------------------------------------------------------
// Declarations
//----------------------------------------------------------------------------------

// Load the GUI resources (must be called before using other functions)
void CguiLoad(void)
{
    // Prevent loading again
    if (resourceLoaded) return;

    // Loading stuff
    //------------------------------------------------------------------------------
    resolution[0] = (float)GetScreenWidth();
    resolution[1] = (float)GetScreenHeight();

    backgroundBuffer1 = LoadRenderTexture((int)resolution[0], (int)resolution[1]);
    backgroundBuffer2 = LoadRenderTexture((int)resolution[0], (int)resolution[1]);
    backgroundBuffer3 = LoadRenderTexture((int)resolution[0], (int)resolution[1]);
    fontBlurBuffer = LoadRenderTexture((int)resolution[0], (int)resolution[1]);

    defaultLogger = NULL;
    nullLogger = CguiNullLogger;
    customFont = GetFontDefault();
    accentColor = CRYSTALGUI_CLITERAL(Color){ 0, 170, 255, 255 };
    foregroundColor = CRYSTALGUI_CLITERAL(Color){ 0, 0, 0, 255 };
    backgroundColor = CRYSTALGUI_CLITERAL(Color){ 255, 255, 255, 255 };
    customFontSize = 30.0f;
    fontShadowOffset = CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f };
    fontShadowBlurRadius = 0.0f;
    fontShadowColor = CRYSTALGUI_CLITERAL(Color){ 0, 0, 0, 255 };
    mainMouseButton = MOUSE_BUTTON_LEFT;
    //------------------------------------------------------------------------------

    // Shader configurations
    //------------------------------------------------------------------------------
    blurShader = LoadShaderFromMemory(0, TextFormat(blurShaderCode, 2.5f));
    shadowShader = LoadShaderFromMemory(0, TextFormat(shadowShaderCode));
    windowShader = LoadShaderFromMemory(0, TextFormat(windowShaderCode));

    blurShaderResLoc = GetShaderLocation(blurShader, "u_resolution");
    blurRadiusLoc = GetShaderLocation(blurShader, "u_blurRadius");
    shadowRoundnessLoc = GetShaderLocation(shadowShader, "u_roundness");
    shadowRectangleLoc = GetShaderLocation(shadowShader, "u_rectangle");
    shadowRadiusLoc = GetShaderLocation(shadowShader, "u_shadowRadius");
    shadowSizeLoc = GetShaderLocation(shadowShader, "u_shadowSize");
    shadowColorLoc = GetShaderLocation(shadowShader, "u_shadowColor");
    shadowOffsetLoc = GetShaderLocation(shadowShader, "u_shadowOffset");
    windowShaderResLoc = GetShaderLocation(windowShader, "u_resolution");
    windowRoundnessLoc = GetShaderLocation(windowShader, "u_roundness");
    windowRectangleLoc = GetShaderLocation(windowShader, "u_rectangle");
    windowTintLoc = GetShaderLocation(windowShader, "u_windowTint");

    CguiShaderUpdate();

    DISABLE_LOGGER;
    CguiSetBlurQuality(7.5f);
    CguiSetBlurRadius(10.0f);
    CguiSetRoundness(10.0f);
    CguiSetShadowRadius(30.0f);
    CguiSetShadowSize(-10.0f);
    CguiSetShadowColor(ColorAlpha(BLACK, 0.375f));
    CguiSetShadowOffset(CRYSTALGUI_CLITERAL(Vector2){ 0.0f, -10.0f });
    CguiSetWindowTint(ColorAlpha(WHITE, 0.625f));
    ENABLE_LOGGER;
    //------------------------------------------------------------------------------

    // Protect functions if the resources are not loaded
    resourceLoaded = true;
}

// Unload the GUI resources (must be called before closing the window)
void CguiUnload(void)
{
    // Prevent unloading before loading
    if (!resourceLoaded) return;

    UnloadShader(blurShader);
    UnloadShader(shadowShader);
    UnloadShader(windowShader);

    UnloadRenderTexture(backgroundBuffer1);
    UnloadRenderTexture(backgroundBuffer2);
    UnloadRenderTexture(backgroundBuffer3);
    UnloadRenderTexture(fontBlurBuffer);
}

// Begin drawing into the background. To make it blur behind the GUI!
void CguiBeginBackground(bool skip)
{
    if (!resourceLoaded || skip) return;

    // Update the background buffers (size) before using
    CguiUpdate();

    BeginTextureMode(backgroundBuffer1);

    // Note: We are clearing the buffer
    ClearBackground(BLANK);

    usedBackground = true;
}

// End the drawing, this function will process the blur
void CguiEndBackground(bool skip)
{
    if (!resourceLoaded || skip) return;
    EndTextureMode();

    // Blur the background and keep it in backgroundBuffer2
    BeginTextureMode(backgroundBuffer2);
        // Note: We are clearing the buffer
        ClearBackground(BLANK);

        BeginShaderMode(blurShader);
            DrawTexturePro(backgroundBuffer1.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], -resolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], resolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
        EndShaderMode();
    EndTextureMode();
}

// Draw the GUI from background buffer
void CguiDraw(void)
{
    usedBackground = false;
    DrawTexturePro(backgroundBuffer1.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], -resolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], resolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
    DrawTexturePro(backgroundBuffer3.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], -resolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], resolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);

    // Background buffer 3 is a dynamic background buffer so we clear it before it's a mess
    BeginTextureMode(backgroundBuffer3);
        ClearBackground(BLANK);
    EndTextureMode();
}

// This will update the global variables (Internally called)
void CguiUpdate(void)
{
    if (IsWindowResized())
    {
        // Update resolution
        //--------------------------------------------------------------------------
        resolution[0] = (float)GetScreenWidth();
        resolution[1] = (float)GetScreenHeight();
        CguiShaderUpdate();
        //--------------------------------------------------------------------------

        // Reload the background buffers
        //--------------------------------------------------------------------------
        UnloadRenderTexture(backgroundBuffer1);
        UnloadRenderTexture(backgroundBuffer2);
        UnloadRenderTexture(backgroundBuffer3);
        UnloadRenderTexture(fontBlurBuffer);

        backgroundBuffer1 = LoadRenderTexture((int)resolution[0], (int)resolution[1]);
        backgroundBuffer2 = LoadRenderTexture((int)resolution[0], (int)resolution[1]);
        backgroundBuffer3 = LoadRenderTexture((int)resolution[0], (int)resolution[1]);
        fontBlurBuffer = LoadRenderTexture((int)resolution[0], (int)resolution[1]);
        //--------------------------------------------------------------------------
    }
}

// Update the shader resolution
void CguiShaderUpdate(void)
{
    // Disable logging
    DISABLE_LOGGER;

    SetShaderValue(blurShader, blurShaderResLoc, resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(windowShader, windowShaderResLoc, resolution, SHADER_UNIFORM_VEC2);

    // Enable logging
    ENABLE_LOGGER;
}

// TraceLog that doesn't print anything, useful to not log something
void CguiNullLogger(int logType, const char *text, ...)
{
    // Do nothing
}

// SDraw shader processed rectangle
void CguiDrawRectangle(Rectangle bounds)
{
    // Rectangle is a 4-component vector in shader so we use array
    static float rectangle[4] = { 0 };
    rectangle[0] = bounds.x;
    rectangle[1] = GetScreenHeight() - bounds.y - bounds.height;
    rectangle[2] = bounds.width;
    rectangle[3] = bounds.height;

    DISABLE_LOGGER;

    // Apply the rectangle
    SetShaderValue(shadowShader, shadowRectangleLoc, rectangle, SHADER_UNIFORM_VEC4);
    SetShaderValue(windowShader, windowRectangleLoc, rectangle, SHADER_UNIFORM_VEC4);

    // Apply shadow shader and window shader on buffer 3
    BeginTextureMode(backgroundBuffer3);
        BeginShaderMode(shadowShader);
            DrawRectangleRec(CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], resolution[0] }, BLANK);
        EndShaderMode();
        BeginShaderMode(windowShader);
            DrawTexturePro(backgroundBuffer2.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], -resolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], resolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, backgroundColor);
        EndShaderMode();
    EndTextureMode();
    ENABLE_LOGGER;
}

//----------------------------------------------------------------------------------
// Basic controls set
//----------------------------------------------------------------------------------

// Label control, shows text
void CguiLabel(CguiLabelParam *cguiLabelParam)
{
    // Update control
    //------------------------------------------------------------------------------
    int len = strlen(cguiLabelParam->param.text);
    Vector2 textdim = MeasureTextEx(customFont, cguiLabelParam->param.text, customFontSize, 1.0f);
    float localBlurRadius = CguiGetBlurRadius();
    //------------------------------------------------------------------------------

    // Draw control, redirect to background buffer when needed.
    //------------------------------------------------------------------------------
    // Put the font in the buffer for blur
    BeginTextureMode(fontBlurBuffer);
        DrawTextEx(customFont, cguiLabelParam->param.text, CRYSTALGUI_CLITERAL(Vector2){(cguiLabelParam->param.bounds.width - textdim.x) / 2.0f + cguiLabelParam->param.bounds.x + fontShadowOffset.x, (cguiLabelParam->param.bounds.height - textdim.y) / 2.0f + cguiLabelParam->param.bounds.y + fontShadowOffset.y}, customFontSize, 1.0f, fontShadowColor);
    EndTextureMode();

    if (usedBackground) BeginTextureMode(backgroundBuffer3);
        // No text shall escape the bounds!
        BeginScissorMode(cguiLabelParam->param.bounds.x, cguiLabelParam->param.bounds.y, cguiLabelParam->param.bounds.width, cguiLabelParam->param.bounds.height);
            // Blur and draw the text's shadow
            CguiSetBlurRadius(fontShadowBlurRadius);
            BeginShaderMode(blurShader);
                DrawTexturePro(fontBlurBuffer.texture, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], -resolution[1] }, CRYSTALGUI_CLITERAL(Rectangle){ 0.0f, 0.0f, resolution[0], resolution[1] }, CRYSTALGUI_CLITERAL(Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
            EndShaderMode();
            CguiSetBlurRadius(localBlurRadius);

            // Draw the text
            DrawTextEx(customFont, cguiLabelParam->param.text, CRYSTALGUI_CLITERAL(Vector2){(cguiLabelParam->param.bounds.width - textdim.x) / 2.0f + cguiLabelParam->param.bounds.x, (cguiLabelParam->param.bounds.height - textdim.y) / 2.0f + cguiLabelParam->param.bounds.y}, customFontSize, 1.0f, foregroundColor);
        EndScissorMode();
    if (usedBackground) EndTextureMode();

    // Clear the font blur buffer
    BeginTextureMode(fontBlurBuffer);
        ClearBackground(BLANK);
    EndTextureMode();
    //------------------------------------------------------------------------------
}

// Button control, returns true when clicked
bool CguiButton(CguiButtonParam *cguiButtonParam)
{
#define TIMER_SPEED 0.0625
    // Update control
    //------------------------------------------------------------------------------
    int len = strlen(cguiButtonParam->param.text);
    Vector2 textdim = MeasureTextEx(customFont, cguiButtonParam->param.text, customFontSize, 1.0f);
    int state = 0;
    bool result = false;
    Color localShadowColor = CguiGetShadowColor();
    Vector2 mousePosition = GetMousePosition();
    CguiLabelParam cguiLabelParam = { 0 };
    cguiLabelParam.param.bounds = cguiButtonParam->param.bounds;
    cguiLabelParam.param.text = cguiButtonParam->param.text;

    if (CheckCollisionPointRec(mousePosition, cguiButtonParam->param.bounds))
    {
        cguiButtonParam->internal.timer += TIMER_SPEED;
        if (cguiButtonParam->internal.timer > localShadowColor.a / 255.0f) cguiButtonParam->internal.timer = localShadowColor.a / 255.0f;
        state = 1;
        if (IsMouseButtonDown(mainMouseButton)) state = 2;
        if (IsMouseButtonReleased(mainMouseButton)) result = true;
    }
    else
    {
        cguiButtonParam->internal.timer -= TIMER_SPEED;
        if (cguiButtonParam->internal.timer < 0.0f) cguiButtonParam->internal.timer = 0.0f;
    }

    switch (state)
    {
    case 0:
        CguiSetWindowTint(ColorAlpha(WHITE, 0.75f));
        CguiSetShadowColor(ColorAlpha(localShadowColor, cguiButtonParam->internal.timer));
        break;
    case 1:
        CguiSetWindowTint(ColorAlpha(WHITE, 0.75f));
        CguiSetShadowColor(ColorAlpha(localShadowColor, cguiButtonParam->internal.timer));
        break;
    case 2:
        CguiSetWindowTint(ColorAlpha(CRYSTALGUI_CLITERAL(Color){ 235, 235, 235, 255 }, 0.75f));
        CguiSetShadowColor(ColorAlpha(localShadowColor, cguiButtonParam->internal.timer));
        break;
    }
    //------------------------------------------------------------------------------

    // Draw control, redirect to background buffer when needed.
    //------------------------------------------------------------------------------
    CguiDrawRectangle(cguiButtonParam->param.bounds);
    CguiLabel(&cguiLabelParam);
    //------------------------------------------------------------------------------

    // Fix the shadow color before return
    CguiSetShadowColor(localShadowColor);
    // Return true if the mouse button is released
    return result;
}

// Label button control, show true when clicked
bool CguiLabelButton(CguiLabelButtonParam *cguiLabelButtonParam)
{

}

// Toggle Button control, returns true when active
bool CguiToggle(CguiToggleParam *cguiToggleParam);

// Toggle Group control, returns active toggle index
int CguiToggleGroup(CguiToggleGroupParam *cguiToggleGroupParam);

// Check Box control, returns true when active
bool CguiCheckBox(CguiCheckBoxParam *cguiCheckBoxParam);

// Combo Box control, returns selected item index
int CguiComboBox(CguiComboBoxParam *cguiComboBoxParam);

// Dropdown Box control, returns selected item
bool CguiDropdownBox(CguiDropdownBoxParam *cguiDropdownBoxParam);

// Spinner control, returns selected value
bool CguiSpinner(CguiSpinnerParam *cguiSpinnerParam);

// Value Box control, updates input text with numbers
bool CguiValueBox(CguiValueBoxParam *cguiValueBoxParam);

// Text Box control, updates input text
bool CguiTextBox(CguiTextBoxParam *cguiTextBoxParam);

// Text Box control with multiple lines
bool CguiTextBoxMulti(CguiTextBoxMultiParam *cguiTextBoxMultiParam);

// Slider control, returns selected value
float CguiSlider(CguiSliderParam *cguiSliderParam);

// Slider Bar control, returns selected value
float CguiSliderBar(CguiSliderBarParam *cguiSliderBarParam);

// Progress Bar control, shows current progress value
float CguiProgressBar(CguiProgressBarParam *cguiProgressBarParam);

// Status Bar control, shows info text
void CguiStatusBar(CguiStatusBarParam *cguiStatusBarParam);

// Dummy control for placeholders
void CguiDummyRec(CguiDummyRecParam *cguiDummyRecParam);

// Grid control, returns mouse cell position
Vector2 CguiGrid(CguiGridParam *cguiGridParam);

//----------------------------------------------------------------------------------
// Advanced controls set
//----------------------------------------------------------------------------------

// List View control, returns selected list item index
int CguiListView(CguiListViewParam *cguiListViewParam);

// List View with extended parameters
int CguiListViewEx(CguiListViewExParam *cguiListViewExParam);

// Message Box control, displays a message
int CguiMessageBox(CguiMessageBoxParam *cguiMessageBoxParam);

// Text Input Box control, ask for text, supports secret
int CguiTextInputBox(CguiTextInputBoxParam *cguiTextInputBoxParam);

// Color Picker control (multiple color controls)
Color CguiColorPicker(CguiColorPickerParam *cguiColorPickerParam);

// Color Panel control
Color CguiColorPanel(CguiColorPanelParam *cguiColorPanelParam);

// Color Bar Alpha control
float CguiColorBarAlpha(CguiColorBarAlphaParam *cguiColorBarAlphaParam);

// Color Bar Hue control
float CguiColorBarHue(CguiColorBarHueParam *cguiColorBarHueParam);

// Set GUI custom font
void CguiSetFont(Font font)
{
    if (font.texture.id > 0)
    {
        customFont = font;
    }
}

// Get GUI custom font
Font CguiGetFont(void)
{
    return customFont;
}

// Set the accent colors for the GUI
void CguiSetAccentColor(Color color)
{
    accentColor = color;
}

// Get the accent colors for the GUI
Color CguiGetAccentColor(void)
{
    return accentColor;
}

// Get the background colors for the GUI
void CguiSetBackgroundColor(Color color)
{
    foregroundColor = color;
}

// Get the background colors for the GUI
Color CguiGetBackgroundColor(void)
{
    return foregroundColor;
}

// Get the foreground colors for the GUI
void CguiSetForegroundColor(Color color)
{
    backgroundColor = color;
}

// Get the foreground colors for the GUI
Color CguiGetForegroundColor(void)
{
    return backgroundColor;
}

// Get the font colors for the GUI
void CguiSetFontShadowColor(Color color)
{
    fontShadowColor = color;
}

// Get the font colors for the GUI
Color CguiGetFontShadowColor(void)
{
    return fontShadowColor;
}

// Set the GUI custom font size
void CguiSetFontSize(float fontSize)
{
    customFontSize = fontSize;
}

// Get the GUI Custom font size
float CguiGetFontSize(void)
{
    return customFontSize;
}

// Set the offset of shadow from text
void CguiSetFontShadowOffset(Vector2 offset)
{
    fontShadowOffset = offset;
}

// Get the offset of shadow for text
Vector2 CguiGetFontShadowOffset(void)
{
    return fontShadowOffset;
}

// Set the blur radius of shadow for text
void CguiSetFontShadowBlurRadius(float value)
{
    fontShadowBlurRadius = value;
}

// Get the blur radius of shadow for text
float CguiGetFontShadowBlurRadius(void)
{
    return fontShadowBlurRadius;
}

// Set the main mouse button for the GUI
void CguiSetMainMouseButton(int button)
{
    mainMouseButton = button;
}

// Get the main mouse button for the GUI
int CguiGetMainMouseButton(void)
{
    return mainMouseButton;
}

//----------------------------------------------------------------------------------
// Shader getters and setters (not always is simple)
//----------------------------------------------------------------------------------

float CguiGetBlurRadius(void)
{
    return blurRadius;
}

float CguiGetBlurQuality(void)
{
    return blurQuality;
}

float CguiGetRoundness(void)
{
    return roundness;
}

float CguiGetShadowRadius(void)
{
    return shadowRadius;
}

float CguiGetShadowSize(void)
{
    return shadowSize;
}

Color CguiGetShadowColor(void)
{
    return CRYSTALGUI_CLITERAL(Color){ shadowColor[0] * 255, shadowColor[1] * 255, shadowColor[2] * 255, shadowColor[3] * 255 };
}

Vector2 CguiGetShadowOffset(void)
{
    return CRYSTALGUI_CLITERAL(Vector2){ shadowOffset[0], shadowOffset[1] };
}

Color CguiGetWindowTint(void)
{
    return CRYSTALGUI_CLITERAL(Color){ windowTint[0] * 255, windowTint[1] * 255, windowTint[2] * 255, windowTint[3] * 255 };
}

void CguiSetBlurRadius(float value)
{
    blurRadius = value;
    DISABLE_LOGGER;
    SetShaderValue(blurShader, blurRadiusLoc, &blurRadius, SHADER_UNIFORM_FLOAT);
    ENABLE_LOGGER;
}

void CguiSetBlurQuality(float value)
{
    blurQuality = value;
    DISABLE_LOGGER;

    // Requires reload of shader because quality is a constant
    UnloadShader(blurShader);
    blurShader = LoadShaderFromMemory(0, TextFormat(blurShaderCode, blurQuality));
    CguiShaderUpdate();

    // Reset the other uniforms
    CguiSetBlurRadius(blurRadius);
    ENABLE_LOGGER;
}

void CguiSetRoundness(float value)
{
    roundness = value;
    DISABLE_LOGGER;
    SetShaderValue(shadowShader, shadowRoundnessLoc, &roundness, SHADER_UNIFORM_FLOAT);
    SetShaderValue(windowShader, windowRoundnessLoc, &roundness, SHADER_UNIFORM_FLOAT);
    ENABLE_LOGGER;
}

void CguiSetShadowRadius(float value)
{
    shadowRadius = value;
    DISABLE_LOGGER;
    SetShaderValue(shadowShader, shadowRadiusLoc, &shadowRadius, SHADER_UNIFORM_FLOAT);
    ENABLE_LOGGER;
}

void CguiSetShadowSize(float value)
{
    shadowSize = value;
    DISABLE_LOGGER;
    SetShaderValue(shadowShader, shadowSizeLoc, &shadowSize, SHADER_UNIFORM_FLOAT);
    ENABLE_LOGGER;
}

void CguiSetShadowColor(Color color)
{
    shadowColor[0] = color.r / 255.0f;
    shadowColor[1] = color.g / 255.0f;
    shadowColor[2] = color.b / 255.0f;
    shadowColor[3] = color.a / 255.0f;

    DISABLE_LOGGER;
    SetShaderValue(shadowShader, shadowColorLoc, shadowColor, SHADER_UNIFORM_VEC4);
    ENABLE_LOGGER;
}

void CguiSetShadowOffset(Vector2 offset)
{
    shadowOffset[0] = offset.x;
    shadowOffset[1] = offset.y;

    DISABLE_LOGGER;
    SetShaderValue(shadowShader, shadowOffsetLoc, shadowOffset, SHADER_UNIFORM_VEC2);
    ENABLE_LOGGER;
}

void CguiSetWindowTint(Color color)
{
    windowTint[0] = color.r / 255.0f;
    windowTint[1] = color.g / 255.0f;
    windowTint[2] = color.b / 255.0f;
    windowTint[3] = color.a / 255.0f;

    DISABLE_LOGGER;
    SetShaderValue(windowShader, windowTintLoc, windowTint, SHADER_UNIFORM_VEC4);
    ENABLE_LOGGER;
}

#endif // CRYSTALGUI_IMPLEMENTATION

#endif // CRYSTALGUI_H
