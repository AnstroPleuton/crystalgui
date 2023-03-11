/*******************************************************************************************
*
*   Crystal GUI - Tests
*
*   DESCRIPTION:
*
*   Test all the functions from Cgui (not including raygui-compatible functions)
*
*   LICENSE: Unmodified MIT License.
*
*   Copyright (c) 2023 Anstro Pleuton
*
*******************************************************************************************/

#define CGUI_IMPLEMENTATION
//#define CRYSTALGUI_LIGHT_THEME
#define CGUI_DARK_THEME
//#define CRYSTALGUI_ALLOW_SHADER_LOGS
#include "crystalgui.h"
#include "raylib.h"
#include <stddef.h>

//------------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    // Only display warnings or above
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Crystal Gui Tests");
    SetTargetFPS(60);

    // Load the Cgui resources
    CguiLoad();
    CguiSetRoundness(5.0f);

    Texture background = LoadTexture("background.png");
    Font font = LoadFontEx("Roboto-Regular.ttf", CguiGetFontProperty().size, NULL, 0);
    FontProp fontProp = CguiGetFontProperty();
    fontProp.size = 20.0f;
    fontProp.font = font;
    CguiSetFontProperty(fontProp);
    bool useWallpaper = false;
    int timesClicked = 0;
    //--------------------------------------------------------------------------------------

    // Gui variables
    //--------------------------------------------------------------------------------------
    CguiButton myButton = { (Rectangle){ 20, 20, 200, 40 }, "Hello there!", 0, 0.0f };
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())
    {
        // Update the gui every frame
        CguiUpdateResolution();

        // Change the settings
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER)) useWallpaper = !useWallpaper;

        if (GetMouseWheelMove() != 0)
        {
            fontProp.size += GetMouseWheelMoveV().x;
            UnloadFont(font);
            font = LoadFontEx("Roboto-Regular.ttf", fontProp.size, NULL, 0);
            fontProp.font = font;
            CguiSetFontProperty(fontProp);
        }
        //----------------------------------------------------------------------------------

        // Process the background, pretty cool looks!
        //----------------------------------------------------------------------------------
        CguiBeginBackground();
            if (useWallpaper) DrawTexturePro(background, (Rectangle){ 0.0f, 0.0f, (float)background.width, (float)background.height }, (Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
            else DrawRectanglePro((Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0.0f, 0.0f }, 0.0f, ColorAlpha(CguiGetColor(CGUI_COLOR_BACKGROUND), 1.0f));
        CguiEndBackground();
        //----------------------------------------------------------------------------------

        // GUI tests
        //----------------------------------------------------------------------------------
        if (CguiUpdateButton(&myButton))
        {
            // Log in console:
            CguiTraceLog("We did it boys! Clicked %i times", ++timesClicked);
        }
        //----------------------------------------------------------------------------------

        // Main Drawing
        //----------------------------------------------------------------------------------
        BeginDrawing();
            // Draw the background that was used by CguiBeginBackground
            CguiDrawBackground();
            CguiDrawButton(&myButton);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);
    UnloadFont(font);
    CguiUnload();        // Unload the Cgui resources
    CloseWindow();
    //--------------------------------------------------------------------------------------
}
