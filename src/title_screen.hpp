#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H
#include "screen.hpp"

class TitleScreen : public Screen {
private:
public:
	void UpdateScreen() override 
	{
		framesCounter++;
		// Press enter to change to GAMEPLAY screen
		if (IsKeyPressed(KEY_ENTER))
		{
			//finishScreen = 1;   // OPTIONS
			finishScreen = 4;   // GAMEPLAY
			//PlaySound(fxCoin);
		}
	}

	void DrawScreen() override 
	{
		// TODO: Draw TITLE screen here!
		DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);

		if ((framesCounter / 30) % 2 == 0) DrawText("PRESS [ENTER] to START", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] to START", 20) / 2, GetScreenHeight() / 2 + 60, 20, DARKGRAY);
	}

	void UnloadScreen() override {}
};

#endif
