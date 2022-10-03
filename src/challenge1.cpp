#include "raylib.h"
#include "challenge1.h"

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Challenge 1");

    InitAudioDevice();      // Initialize audio device

    // Load global data (assets that must be available in all screens, i.e. font)
    font = LoadFont("resources/mecha.png");
    music = LoadMusicStream("resources/ambient.ogg");
    fxCoin = LoadSound("resources/coin.wav");
    
    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    // Setup and init first screen
    currentScreen = LOGO;

    //InitLogoScreen();
    logoScreen->InitScreen();

    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload current screen data before closing
    switch (currentScreen)
    {
        case LOGO: logoScreen->UnloadScreen(); break;
        case TITLE: titleScreen->UnloadScreen(); break;
        case GAMEPLAY: gameScreen->UnloadScreen(); break;
        case ENDING: endingScreen->UnloadScreen(); break;
        default: break;
    }

    // Unload global data loaded
    UnloadFont(font);
    UnloadMusicStream(music);
    UnloadSound(fxCoin);
    gameScreen->DeleteTextures();
    delete logoScreen;
    delete titleScreen;
    delete gameScreen;
    delete endingScreen;

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
static void ChangeToScreen(Screens screen)
{
    // Unload current screen
    switch (currentScreen)
    {
        case LOGO: logoScreen->UnloadScreen(); break;
        case TITLE: titleScreen->UnloadScreen(); break;
        case GAMEPLAY: gameScreen->UnloadScreen(); break;
        case ENDING: endingScreen->UnloadScreen(); break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO: logoScreen->InitScreen(); break;
        case TITLE: titleScreen->InitScreen(); break;
        case GAMEPLAY: gameScreen->InitScreen(); break;
        case ENDING: endingScreen->InitScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Request transition to next screen
static void TransitionToScreen(Screens screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO: logoScreen->UnloadScreen(); break;
                case TITLE: titleScreen->UnloadScreen(); break;
                case OPTIONS: optionsScreen->UnloadScreen(); break;
                case GAMEPLAY: gameScreen->UnloadScreen(); break;
                case ENDING: endingScreen->UnloadScreen(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                case LOGO: logoScreen->InitScreen(); break;
                case TITLE: titleScreen->InitScreen(); break;
                case GAMEPLAY: gameScreen->InitScreen(); break;
                case ENDING: endingScreen->InitScreen(); break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = NONE;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Update and draw game frame
static void UpdateDrawFrame()
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateMusicStream(music);       // NOTE: Music keeps playing between screens

    if (!onTransition)
    {
        switch(currentScreen)
        {
            case LOGO:
            {
                logoScreen->UpdateScreen();

                if (logoScreen->FinishScreen()) TransitionToScreen(TITLE);

            } break;
            case TITLE:
            {
                titleScreen->UpdateScreen();

                if (titleScreen->FinishScreen() == 3) TransitionToScreen(OPTIONS);
                else if (titleScreen->FinishScreen() == 4) TransitionToScreen(GAMEPLAY);

            } break;
            case OPTIONS:
            {
                optionsScreen->UpdateScreen();

                if (optionsScreen->FinishScreen()) TransitionToScreen(TITLE);

            } break;
            case GAMEPLAY:
            {
                gameScreen->UpdateScreen();

                if (gameScreen->FinishScreen() == 5) TransitionToScreen(ENDING);
                //else if (FinishGameplayScreen() == 3) TransitionToScreen(TITLE);

            } break;
            case ENDING:
            {
                endingScreen->UpdateScreen();

                if (endingScreen->FinishScreen() == 2) TransitionToScreen(TITLE);

            } break;
            default: break;
        }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        switch(currentScreen)
        {
            case LOGO: logoScreen->DrawScreen(); break;
            case TITLE: titleScreen->DrawScreen(); break;
            case OPTIONS: optionsScreen->DrawScreen(); break;
            case GAMEPLAY: gameScreen->DrawScreen(); break;
            case ENDING: endingScreen->DrawScreen(); break;
            default: break;
        }

        // Draw full screen rectangle in front of everything
        if (onTransition) DrawTransition();

        //DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
