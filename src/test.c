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
#include "crystalgui.h"
#include "raylib.h"
#include "roboto_regular.h"
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

    // Font settings
    FontProp fontProp = CguiGetFontProperty();
    fontProp.size = 20.0f;
    fontProp.font = LoadFont_RobotoRegular();
    CguiSetFontProperty(fontProp);

    Texture background = LoadTexture("background.png");
    bool useWallpaper = false;
    int timesClicked = 0;
    //--------------------------------------------------------------------------------------

    // Gui variables
    //--------------------------------------------------------------------------------------
    CguiButton myButton = { (Rectangle){ 20, 20, 200, 40 }, "Hello there!", 0, 0.0f };

    List *entries = CreateList(sizeof(CguiButton));
    *(CguiButton *)AddElement(0, entries)->data = (CguiButton){ { 0.0f, 0.0f, 0.0f, 0.0f }, "One", 0, 0.0f };
    *(CguiButton *)AddElement(1, entries)->data = (CguiButton){ { 0.0f, 0.0f, 0.0f, 0.0f }, "Two", 0, 0.0f };
    *(CguiButton *)AddElement(2, entries)->data = (CguiButton){ { 0.0f, 0.0f, 0.0f, 0.0f }, "Three", 0, 0.0f };
    *(CguiButton *)AddElement(3, entries)->data = (CguiButton){ { 0.0f, 0.0f, 0.0f, 0.0f }, "So on", 0, 0.0f };
    CguiDropDownButton ddButton = { (Rectangle){ 20, 70, 200, 40 }, entries, 3, 0, 0, 0.0f, 0.0f, false, 0.0f };
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())
    {
        // Update the gui every frame
        CguiUpdateResolution();

        if (IsKeyPressed(KEY_ENTER)) useWallpaper = !useWallpaper;
        if (GetMouseWheelMove() != 0) fontProp.size += GetMouseWheelMoveV().x;

        // Process the background, pretty cool looks!
        //----------------------------------------------------------------------------------
        CguiBeginBackground();
            if (useWallpaper) DrawTexturePro(background, (Rectangle){ 0.0f, 0.0f, (float)background.width, (float)background.height }, (Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
            else DrawRectanglePro((Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0.0f, 0.0f }, 0.0f, ColorAlpha(CguiGetColor(CGUI_COLOR_BACKGROUND), 1.0f));
        CguiEndBackground();
        //----------------------------------------------------------------------------------

        // Update Cgui
        //----------------------------------------------------------------------------------
        if (CguiUpdateButton(&myButton))
        {
            CguiUpdateResolution();
        }
        CguiUpdateDropDownButton(&ddButton);
        //----------------------------------------------------------------------------------

        // Main Drawing
        //----------------------------------------------------------------------------------
        BeginDrawing();
            // Draw the background that was used by CguiBeginBackground
            CguiDrawBackground();

            // Draw Cgui
            //------------------------------------------------------------------------------
            CguiDrawButton(&myButton);
            CguiDrawDropDownButton(&ddButton);
            //------------------------------------------------------------------------------
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Cgui Variables de-initialization
    //--------------------------------------------------------------------------------------
    ClearList(entries);
    //--------------------------------------------------------------------------------------

    // De-initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);
    CguiUnload();        // Unload the Cgui resources
    CloseWindow();
    //--------------------------------------------------------------------------------------
}
