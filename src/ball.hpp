#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "player.hpp"
#include "brick.hpp"

class Ball {
private:
    Vector2 _position;
    Vector2 _speed;
    float _radius;
    bool _active;

    Texture2D _texture;

public:
    Vector2 Position() const { return _position; }
    Vector2 Speed() const { return _speed; }
    float Radius() const { return _radius; }
    bool Active() const { return _active; }
    Texture2D Texture() const { return _texture; }

    void Init(Vector2 position, Vector2 speed, float radius, bool active)
    {
        this->_position = position;
        this->_speed = speed;
        this->_radius = radius;
        this->_active = active;
        _texture = LoadTexture("resources/ball.png");
    }

    void Move(Player* player, Brick bricks[][BRICKS_PER_LINE])
    {
        // Ball movement logic
        _position.x += _speed.x;
        _position.y += _speed.y;

        // Collision logic: ball vs screen-limits
        if (((_position.x + _radius) >= SCR_WIDTH) || ((_position.x - _radius) <= 0)) _speed.x *= -1;
        if ((_position.y - _radius) <= 0) _speed.y *= -1;

        // Collision logic: ball vs player
        if (CheckCollisionCircleRec(_position, _radius, player->Bounds()))
        {
            _speed.y *= -1;
            _speed.x = (_position.x - (player->Position().x + player->Size().x / 2)) / player->Size().x * 5.0f;
        }

        // Collision logic: ball vs bricks
        for (int j = 0; j < BRICKS_LINES; j++)
        {
            for (int i = 0; i < BRICKS_PER_LINE; i++)
            {
                if (bricks[j][i].Active() && (CheckCollisionCircleRec(_position, _radius, bricks[j][i].Bounds())))
                {
                    bricks[j][i].Destroy();
                    _speed.y *= -1;
                    break;
                }
            }
        }

        // Game ending logic
        if ((_position.y + _radius) >= SCR_HEIGHT)
        {
            _position.x = player->Position().x + player->Size().x / 2;
            _position.y = player->Position().y - _radius - 1.0f;
            _speed = Vector2{ 0, 0 };
            _active = false;

            player->GetDamage();
        }
    }

    void ResetPosition(Player* player)
    {
        _position.x = player->Position().x + player->Size().x / 2;
    }

    void Activate() 
    {
        _active = true;
        _speed = Vector2{ 0, -5.0f };
    }

    void DeleteTexture() {
        UnloadTexture(_texture);
    }
};
#endif // !BALL_H