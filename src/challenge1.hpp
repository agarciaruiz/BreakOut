#ifndef CHALLENGE1_H
#define CHALLENGE1_H

#include "logo_screen.hpp"
#include "title_screen.hpp"
#include "game_screen.hpp"
#include "ending_screen.hpp"
#include "options_screen.hpp"

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
enum Screens { NONE, LOGO, TITLE, OPTIONS, GAMEPLAY, ENDING };
Screens currentScreen = Screens::LOGO;
Music music = { 0 };
Sound fxCoin = { 0 };

LogoScreen* logoScreen = new LogoScreen();
TitleScreen* titleScreen = new TitleScreen();
GameScreen* gameScreen = new GameScreen();
EndingScreen* endingScreen = new EndingScreen();
OptionsScreen* optionsScreen = new OptionsScreen();

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static Screens transToScreen = Screens::NONE;

int gameResult = -1;            // Game result: 0 - Loose, 1 - Win, -1 - Not defined
bool gamePaused = false;        // Game paused state toggle

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void ChangeToScreen(Screens screen);     // Change to screen, no transition effect

static void TransitionToScreen(Screens screen); // Request transition to next screen
static void UpdateTransition(void);         // Update transition effect
static void DrawTransition(void);           // Draw transition effect (full-screen rectangle)

static void UpdateDrawFrame();          // Update and draw one frame

#endif