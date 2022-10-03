#ifndef LOGOSCREEN_H
#define LOGOSCREEN_H
#include "screen.h"

class LogoScreen : public Screen {
private:
	int logoPositionX = 0;
	int logoPositionY = 0;

	int lettersCount = 0;

	int topSideRecWidth = 0;
	int leftSideRecHeight = 0;

	int bottomSideRecWidth = 0;
	int rightSideRecHeight = 0;

	float alpha = 1.0f;         // Useful for fading

	Texture2D texLogo;

public:

	void InitScreen() override
	{
		finishScreen = 0;
		framesCounter = 0;
		lettersCount = 0;

		logoPositionX = GetScreenWidth() / 2 - 128;
		logoPositionY = GetScreenHeight() / 2 - 128;

		topSideRecWidth = 16;
		leftSideRecHeight = 16;
		bottomSideRecWidth = 16;
		rightSideRecHeight = 16;

		alpha = 1.0f;

		texLogo = LoadTexture("resources/raylib_logo.png");
	}

	void UpdateScreen() override
	{
		framesCounter++;

		if (framesCounter > 180)
		{
			finishScreen = 2;
			framesCounter = 0;      // Reset counter... will be used later...
		}
	}

	void DrawScreen() override
	{
		DrawTexture(texLogo, SCR_WIDTH/2 - texLogo.width/2, SCR_HEIGHT/2 - texLogo.height/2, WHITE);
	}

	void UnloadScreen() override {}

};
#endif // !LOGO_SCREEN_H
