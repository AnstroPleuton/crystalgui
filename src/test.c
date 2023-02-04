/*******************************************************************************************
*
*   Crystal GUI - Tests
*
*   DESCRIPTION:
*
*   Test all the functions from CrystalGui (not including raygui-compatible functions)
*
*   LICENSE: Unmodified MIT License.
*
*   Copyright (c) 2023 Anstro Pleuton
*
*******************************************************************************************/

#include "raylib.h"

#define CRYSTALGUI_IMPLEMENTATION
#include "crystalgui.h"

//------------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Crystal Gui Tests");
    SetExitKey(0);
    SetTargetFPS(60);

    // Load the CrystalGui resources
    CrystalGuiLoad();

    Texture background = LoadTexture("../background.png");
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())
    {
        // GUI tests
        //----------------------------------------------------------------------------------
        // ... Seems pretty empty here ...
        //----------------------------------------------------------------------------------

        CrystalGuiBeginBackground();
            // Draw the background to be blurred!
            DrawTexturePro(background, (Rectangle){ 0.0f, 0.0f, (float)background.width, (float)background.height }, (Rectangle){ 0.0f, 0.0f, (float)screenWidth, (float)screenHeight }, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
        CrystalGuiEndBackground();
        
        BeginDrawing();
            CrystalGuiDraw();
        EndDrawing();
    }

    // De-initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);
    CrystalGuiUnload();        // Unload the CrystalGui resources
    CloseWindow();
    //--------------------------------------------------------------------------------------
}
