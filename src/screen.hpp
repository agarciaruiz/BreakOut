#ifndef SCREENS_H
#define SCREENS_H

#define SCR_WIDTH 800
#define SCR_HEIGHT 450

#include "raylib.h"

class Screen {
protected:
	int framesCounter = 0;
	int finishScreen = 0;

public:
	int FinishScreen() const { return finishScreen; }

	virtual void InitScreen()
	{    
		framesCounter = 0;
		finishScreen = 0;
	}

	virtual void UpdateScreen(){}
	virtual void DrawScreen(){}
	virtual void UnloadScreen(){}
};
#endif // SCREENS_H