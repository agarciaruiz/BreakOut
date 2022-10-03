#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#define BRICKS_POSITION_Y       50

#include "screen.hpp"
#include "player.hpp"
#include "ball.hpp"
#include "brick.hpp"

class GameScreen : public Screen {
private:
	bool gamePaused = false;
	Player player;
	Ball ball;
	Brick bricks[BRICKS_LINES][BRICKS_PER_LINE];

	Vector2 playerPos = Vector2{ SCR_WIDTH / 2, SCR_HEIGHT * 7 / 8 };
	Vector2 playerSpeed = Vector2{ 8.0f, 0.0f };
	Vector2 playerSize = Vector2{ 100, 24 };
	int playerLifes = PLAYER_LIFES;

	float ballRadius = 10.0f;
	Vector2 ballPosition;
	bool ballActive = false;
	Vector2 ballSpeed = Vector2{ 4.0f, 4.0f };

	Vector2 brickSize = Vector2{ SCR_WIDTH / BRICKS_PER_LINE, 20 };
	Vector2 brickPosition = {0};
	Rectangle brickBounds = {0};
	bool brickActive = true;
	Texture2D brickTexture;


public:
	void InitScreen() override 
	{
		framesCounter = 0;
		finishScreen = 0;
		brickTexture = LoadTexture("resources/brick.png");
		player.Init(playerPos, playerSpeed, playerSize, playerLifes);

		ballPosition = Vector2{ player.Position().x + player.Size().x / 2, player.Position().y - ballRadius * 2 };
		ball.Init(ballPosition, ballSpeed, ballRadius, ballActive);

		// Bricks Init
		for (int j = 0; j < BRICKS_LINES; j++)
		{
			for (int i = 0; i < BRICKS_PER_LINE; i++)
			{
				brickPosition = Vector2{ i * brickSize.x, j * brickSize.y + BRICKS_POSITION_Y };
				brickBounds = Rectangle{ brickPosition.x, brickPosition.y, brickSize.x, brickSize.y };
				bricks[j][i].Init(brickPosition, brickSize, brickBounds, brickActive, brickTexture);
			}
		}
	}

	void UpdateScreen() override
	{
		if (IsKeyPressed('P')) gamePaused = !gamePaused;    // Pause button logic

		// Press enter or tap to change to ENDING screen
		if (!gamePaused)
		{
			int dir;
			if (IsKeyDown(KEY_LEFT))
				dir = -1;
			else if (IsKeyDown(KEY_RIGHT))
				dir = 1;
			else
				dir = 0;

			player.MoveX(dir);

			if(ball.Active())
			{
				ball.Move(&player, bricks);

				if (player.Lifes() <= 0)
				{
					finishScreen = 5;
					player.ResetLifes();
					framesCounter = 0;
				}
			}
			else 
			{
				// Reset ball position
				ball.ResetPosition(&player);

				if (IsKeyPressed(KEY_SPACE))
				{
					// Activate ball logic
					ball.Activate();
				}
			}
		}
	}

	void DrawScreen() override
	{
		/*
		DrawRectangle(player.Position().x, player.Position().y, player.Size().x, player.Size().y, BLACK);   // Draw player bar
		DrawCircleV(ball.Position(), ball.Radius(), MAROON);    // Draw ball

		// Draw bricks
		for (int j = 0; j < BRICKS_LINES; j++)
		{
			for (int i = 0; i < BRICKS_PER_LINE; i++)
			{
				if (bricks[j][i].Active())
				{
					if ((i + j) % 2 == 0) DrawRectangle(bricks[j][i].Position().x, bricks[j][i].Position().y, bricks[j][i].Size().x, bricks[j][i].Size().y, GRAY);
					else DrawRectangle(bricks[j][i].Position().x, bricks[j][i].Position().y, bricks[j][i].Size().x, bricks[j][i].Size().y, DARKGRAY);
				}
			}
		}
		*/

		DrawTextureEx(player.Texture(), player.Position(), 0.0f, 1.0f, WHITE);   // Draw player

		DrawTexture(ball.Texture(), ball.Position().x - ball.Radius() / 2, ball.Position().y - ball.Radius() / 2, MAROON);    // Draw ball

		// Draw bricks
		for (int j = 0; j < BRICKS_LINES; j++)
		{
			for (int i = 0; i < BRICKS_PER_LINE; i++)
			{
				if (bricks[j][i].Active())
				{
					// NOTE: Texture is not scaled, just using original size

					if ((i + j) % 2 == 0) DrawTextureEx(bricks[j][i].Texture(), bricks[j][i].Position(), 0.0f, 1.0f, GRAY);
					else DrawTextureEx(bricks[j][i].Texture(), bricks[j][i].Position(), 0.0f, 1.0f, DARKGRAY);
				}
			}
		}

		for (int i = 0; i < player.Lifes(); i++) DrawRectangle(20 + 40 * i, SCR_HEIGHT - 30, 35, 10, LIGHTGRAY);

		if (gamePaused) DrawText("GAME PAUSED", SCR_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCR_HEIGHT / 2 + 60, 40, GRAY);
	}

	void UnloadScreen() override
	{

	}

	void DeleteTextures()
	{
		player.DeleteTexture();
		ball.DeleteTexture();
		for (int j = 0; j < BRICKS_LINES; j++)
		{
			for (int i = 0; i < BRICKS_PER_LINE; i++)
			{
				bricks[j][i].DeleteTexture();
			}
		}
	}
};

#endif