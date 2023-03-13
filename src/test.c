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
    // CguiSetRoundness(5.0f);

    // Font settings
    FontProp fontProp = CguiGetFontProperty();
    fontProp.size = 20.0f;
    fontProp.font = LoadFontEx("../res/Roboto-Regular.ttf", fontProp.size, NULL, 0);
    CguiSetFontProperty(fontProp);

    Texture background = LoadTexture("../res/background.png");
    bool useWallpaper = false, theme = false;
    int timesClicked = 0;
    //--------------------------------------------------------------------------------------

    // Gui variables setup
    //--------------------------------------------------------------------------------------
    List *entries = CreateList(sizeof(CguiButton));
    const char *texts[] = { "Select Tool", "Wrench", "Hammer", "Blade", "Screw you", "Tape", "Glue" };
    for (int i = 0; i < 7; i++)
    {
        CguiButton temp = { { 0.0f, 0.0f, 0.0f, 0.0f }, texts[i], 0, 0.0f };
        *(CguiButton *)AddElement(i, entries)->data = temp;
    }
    //--------------------------------------------------------------------------------------

    // Gui variables
    //--------------------------------------------------------------------------------------
    CguiButton myButton = { (Rectangle){ 20, 20, 200, 40 }, "Button" };
    CguiDropDownButton ddButton = { { 20, 70, 200, 40 }, entries, 0, 0 };
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())
    {
        // Update the gui every frame
        CguiUpdateResolution();

        if (IsKeyPressed(KEY_ENTER)) useWallpaper = !useWallpaper;
        if (IsKeyPressed(KEY_SPACE)) { theme = !theme; theme ? CguiSetLightTheme() : CguiSetDarkTheme(); }
        if (IsKeyPressed(KEY_UP)) { CguiButton temp = { { 0.0f, 0.0f, 0.0f, 0.0f }, "New entry", 0, 0.0f }; *(CguiButton *)AddElement(GetListSize(entries), entries)->data = temp; }
        if (IsKeyPressed(KEY_DOWN)) { RemoveElement(GetListSize(entries) - 1, entries); }
        if (IsKeyPressed(KEY_RIGHT)) for (int i = 0; i < 5; i++) { CguiButton temp = { { 0.0f, 0.0f, 0.0f, 0.0f }, "5 more entries", 0, 0.0f }; *(CguiButton *)AddElement(GetListSize(entries), entries)->data = temp; }
        if (IsKeyPressed(KEY_LEFT)) for (int i = 0; i < 5; i++) { { RemoveElement(GetListSize(entries) - 1, entries); } }
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
        CguiUpdateButton(&myButton);
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
