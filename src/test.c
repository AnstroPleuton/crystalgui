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

#define CRYSTALGUI_IMPLEMENTATION
//#define CRYSTALGUI_SHADER_LOGS
#include "crystalgui.h"
#include "raylib.h"

void UpdateBackground(Texture background, int screenWidth, int screenHeight)
{
    CguiBeginBackground(false);
        // Draw the background to be blurred!
        DrawTexturePro(background, (Rectangle){ 0.0f, 0.0f, (float)background.width, (float)background.height }, (Rectangle){ 0.0f, 0.0f, (float)screenWidth, (float)screenHeight }, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
        // ClearBackground(WHITE);
    CguiEndBackground(false);
}

void ShaderControl()
{
    if (IsKeyDown(KEY_Q)) { CguiSetBlurRadius(CguiGetBlurRadius() + 1.0f); }
    if (IsKeyDown(KEY_A)) { CguiSetBlurRadius(CguiGetBlurRadius() - 1.0f); }
    if (IsKeyDown(KEY_Z)) { CguiSetBlurQuality(CguiGetBlurQuality() + 1.0f); }
    if (IsKeyDown(KEY_X)) { CguiSetBlurQuality(CguiGetBlurQuality() - 1.0f); }
    if (IsKeyDown(KEY_W)) { CguiSetRoundness(CguiGetRoundness() + 1.0f); }
    if (IsKeyDown(KEY_S)) { CguiSetRoundness(CguiGetRoundness() - 1.0f); }
    if (IsKeyDown(KEY_E)) { CguiSetShadowRadius(CguiGetShadowRadius() + 1.0f); }
    if (IsKeyDown(KEY_D)) { CguiSetShadowRadius(CguiGetShadowRadius() - 1.0f); }
    if (IsKeyDown(KEY_R)) { CguiSetShadowSize(CguiGetShadowSize() + 1.0f); }
    if (IsKeyDown(KEY_F)) { CguiSetShadowSize(CguiGetShadowSize() - 1.0f); }
    if (IsKeyDown(KEY_Y)) { CguiSetShadowOffset((Vector2){ CguiGetShadowOffset().x, CguiGetShadowOffset().y - 1.0f }); }
    if (IsKeyDown(KEY_H)) { CguiSetShadowOffset((Vector2){ CguiGetShadowOffset().x, CguiGetShadowOffset().y + 1.0f }); }
    if (IsKeyDown(KEY_G)) { CguiSetShadowOffset((Vector2){ CguiGetShadowOffset().x - 1.0f, CguiGetShadowOffset().y }); }
    if (IsKeyDown(KEY_J)) { CguiSetShadowOffset((Vector2){ CguiGetShadowOffset().x + 1.0f, CguiGetShadowOffset().y }); }
    if (IsKeyDown(KEY_O))             { CguiSetShadowColor((Color){ CguiGetShadowColor().r + 1.0f, CguiGetShadowColor().g, CguiGetShadowColor().b, CguiGetShadowColor().a }); }
    if (IsKeyDown(KEY_K))             { CguiSetShadowColor((Color){ CguiGetShadowColor().r - 1.0f, CguiGetShadowColor().g, CguiGetShadowColor().b, CguiGetShadowColor().a }); }
    if (IsKeyDown(KEY_P))             { CguiSetShadowColor((Color){ CguiGetShadowColor().r, CguiGetShadowColor().g + 1.0f, CguiGetShadowColor().b, CguiGetShadowColor().a }); }
    if (IsKeyDown(KEY_L))             { CguiSetShadowColor((Color){ CguiGetShadowColor().r, CguiGetShadowColor().g - 1.0f, CguiGetShadowColor().b, CguiGetShadowColor().a }); }
    if (IsKeyDown(KEY_LEFT_BRACKET))  { CguiSetShadowColor((Color){ CguiGetShadowColor().r, CguiGetShadowColor().g, CguiGetShadowColor().b + 1.0f, CguiGetShadowColor().a }); }
    if (IsKeyDown(KEY_SEMICOLON))     { CguiSetShadowColor((Color){ CguiGetShadowColor().r, CguiGetShadowColor().g, CguiGetShadowColor().b - 1.0f, CguiGetShadowColor().a }); }
    if (IsKeyDown(KEY_RIGHT_BRACKET)) { CguiSetShadowColor((Color){ CguiGetShadowColor().r, CguiGetShadowColor().g, CguiGetShadowColor().b, CguiGetShadowColor().a + 1.0f }); }
    if (IsKeyDown(KEY_APOSTROPHE))    { CguiSetShadowColor((Color){ CguiGetShadowColor().r, CguiGetShadowColor().g, CguiGetShadowColor().b, CguiGetShadowColor().a - 1.0f }); }
    if (IsKeyDown(KEY_C))             { CguiSetFontSize(CguiGetFontSize() + 1.0f); }
    if (IsKeyDown(KEY_V))             { CguiSetFontSize(CguiGetFontSize() - 1.0f); }
    if (IsKeyDown(KEY_B))             { CguiSetFontShadowBlurRadius(CguiGetFontShadowBlurRadius() + 0.1f); }
    if (IsKeyDown(KEY_N))             { CguiSetFontShadowBlurRadius(CguiGetFontShadowBlurRadius() - 0.1f); }
    if (IsKeyDown(KEY_M))             { CguiSetFontShadowOffset((Vector2){ CguiGetFontShadowOffset().x - 0.1f, CguiGetFontShadowOffset().y }); }
    if (IsKeyDown(KEY_COMMA))         { CguiSetFontShadowOffset((Vector2){ CguiGetFontShadowOffset().x, CguiGetFontShadowOffset().y + 0.1f }); }
    if (IsKeyDown(KEY_PERIOD))        { CguiSetFontShadowOffset((Vector2){ CguiGetFontShadowOffset().x, CguiGetFontShadowOffset().y - 0.1f }); }
    if (IsKeyDown(KEY_SLASH))         { CguiSetFontShadowOffset((Vector2){ CguiGetFontShadowOffset().x + 0.1f, CguiGetFontShadowOffset().y }); }
}

void DrawDebug(void)
{
    DrawText(TextFormat("Blur Radius: %f\nBlur Quality%f\nRoundness: %f\nShadow Radius: %f\nShadow Size: %f", CguiGetBlurRadius(), CguiGetBlurQuality(), CguiGetRoundness(), CguiGetShadowRadius(), CguiGetShadowSize()), 20, 20, 20, BLACK);
    DrawText(TextFormat("\n\n\n\n\nShadow Offset: %f, %f", CguiGetShadowOffset().x, CguiGetShadowOffset().y), CguiGetShadowOffset().x + 20, CguiGetShadowOffset().y + 20, 20, BLACK);
    DrawText(TextFormat("\n\n\n\n\n\nShadow Color: %d, %d, %d, %d", CguiGetShadowColor().r, CguiGetShadowColor().g, CguiGetShadowColor().b, CguiGetShadowColor().a), 20, 20, 20, CguiGetShadowColor());
    DrawText(TextFormat("\n\n\n\n\n\n\nFont size: %f\nFont shadow radius: %f\nFont shadow offset: %f, %f\n", CguiGetFontSize(), CguiGetFontShadowBlurRadius(), CguiGetFontShadowOffset().x, CguiGetFontShadowOffset().y), 20, 20, 20, BLACK);
}

//------------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Crystal Gui Tests");
    SetExitKey(0);
    SetTargetFPS(60);

    // Load the Cgui resources
    CguiLoad();

    Texture background = LoadTexture("background.png");
    Font nunito = LoadFontEx("nunito.ttf", CguiGetFontSize(), NULL, 0);
    bool displayLog = false;
    float buttonOneTimer = 0.0f;
    float buttonTwoTimer = 0.0f;
    float buttonThrTimer = 0.0f;
    float buttonFouTimer = 0.0f;
    CguiSetFont(nunito);
    //--------------------------------------------------------------------------------------

    // Gui variables
    //--------------------------------------------------------------------------------------
    CguiButtonParam myButton1 = { { (Rectangle){ 20.0f, 20.0f, 140.0f, 40.0f }, "Click me!" } };
    CguiButtonParam myButton2 = { { (Rectangle){ 180.0f, 20.0f, 140.0f, 40.0f }, "And me!" } };
    CguiButtonParam myButton3 = { { (Rectangle){ 20.0f, 80.0f, 140.0f, 40.0f }, "Me too!" } };
    CguiButtonParam myButton4 = { { (Rectangle){ 180.0f, 80.0f, 140.0f, 40.0f }, "Me me!" } };
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())
    {
        // Change the shader settings
        //----------------------------------------------------------------------------------
        ShaderControl();
        if (IsKeyPressed(KEY_SPACE)) displayLog = !displayLog;
        if (GetMouseWheelMove() != 0) CguiSetFontSize(CguiGetFontSize() + GetMouseWheelMove());
        //----------------------------------------------------------------------------------

        // Process the background, pretty cool looks!
        //----------------------------------------------------------------------------------
        UpdateBackground(background, screenWidth, screenHeight);
        //----------------------------------------------------------------------------------

        // GUI tests
        //----------------------------------------------------------------------------------
        CguiButton(&myButton1);
        CguiButton(&myButton2);
        CguiButton(&myButton3);
        CguiButton(&myButton4);
        //----------------------------------------------------------------------------------

        // Main Drawing
        //----------------------------------------------------------------------------------
        BeginDrawing();
            // Draw the GUI before drawing anything else
            CguiDraw();
            if(displayLog) DrawDebug();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);
    UnloadFont(nunito);
    CguiUnload();        // Unload the Cgui resources
    CloseWindow();
    //--------------------------------------------------------------------------------------
}
