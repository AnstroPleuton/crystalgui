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
//#define CGUI_LIGHT_THEME
#define CGUI_DARK_THEME

#include "crystalgui.h"
#include "raylib.h"

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
    fontProp.font = LoadFontEx("../res/Roboto-Regular.ttf", fontProp.size, NULL, 0);
    CguiSetFontProperty(fontProp);

    Texture background = LoadTexture("../res/background.png");
    bool useWallpaper = false, theme = false;
    int timesClicked = 0;

    // Gui variables
    CguiButton myButton = CguiCreateButton((Rectangle){ 20, 70, 200, 40 }, "Button");
    CguiDropDownButton ddButton = CguiCreateDropDownButton((Rectangle){ 20, 20, 200, 40 }, (char *[]){ "Select Tool", "Wrench", "Hammer", "Blade", "Screw you", "Tape", "Glue" }, 7, 0);
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())
    {
        // Update the gui every frame
        CguiUpdateResolution();

        if (IsKeyPressed(KEY_ENTER)) useWallpaper = !useWallpaper;
        if (IsKeyPressed(KEY_SPACE)) { theme = !theme; theme ? CguiSetLightTheme() : CguiSetDarkTheme(); }
        if (GetMouseWheelMove() != 0) fontProp.size += GetMouseWheelMoveV().x;

        // Process the background, pretty cool looks!
        CguiBeginBackground();
            if (useWallpaper) DrawTexturePro(background, (Rectangle){ 0.0f, 0.0f, (float)background.width, (float)background.height }, (Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
            else DrawRectanglePro((Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0.0f, 0.0f }, 0.0f, ColorAlpha(CguiGetColor(CGUI_COLOR_BACKGROUND), 1.0f));
        CguiEndBackground();

        // Update Cgui
        CguiUpdateButton(&myButton);
        CguiUpdateDropDownButton(&ddButton);

        // Main Drawing
        BeginDrawing();
            // Draw the background that was used by CguiBeginBackground
            CguiDrawBackground();

            // Draw Cgui
            CguiDrawButton(&myButton);
            CguiDrawDropDownButton(&ddButton);
        EndDrawing();
    }

    // De-initialization
    //--------------------------------------------------------------------------------------
    CguiDeleteButton(&myButton);
    CguiDeleteDropDownButton(&ddButton);
    UnloadTexture(background);
    CguiUnload();        // Unload the Cgui resources
    CloseWindow();
    //--------------------------------------------------------------------------------------
}
