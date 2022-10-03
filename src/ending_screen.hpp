#ifndef ENDINGSCREEN_H
#define ENDING_H
#include "screen.hpp"

class EndingScreen : public Screen {
private:
public:
	void UpdateScreen() override 
	{
		framesCounter++;

		// Press enter or tap to return to TITLE screen
		if (IsKeyPressed(KEY_ENTER))
		{
			finishScreen = 2;
			//PlaySound(fxCoin);
		}
	}

	void DrawScreen() override 
	{
		DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);

		if ((framesCounter / 30) % 2 == 0) DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 + 80, 20, GRAY);
	}

	void UnloadScreen() override {}
};

#endif