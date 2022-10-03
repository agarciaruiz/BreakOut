#ifndef PLAYER_H
#define PLAYER_H
#define PLAYER_LIFES             5


#include "raylib.h"
#include "screen.hpp"

class Player {
private:
    Vector2 _position;
    Vector2 _speed;
    Vector2 _size;
    Rectangle _bounds;
    int _lifes;

    Texture2D _texture;

public:
    Vector2 Position () const { return _position; }
    Vector2 Speed () const { return _speed; }
    Vector2 Size () const { return _size; }
    Rectangle Bounds () const { return _bounds; }
    int Lifes () const { return _lifes; }
    Texture2D Texture() const { return _texture; }


    void Init(Vector2 position, Vector2 speed, Vector2 size, int lifes)
    {
        this->_position = position;
        this->_speed = speed;
        this->_size = size;
        this->_lifes = lifes;
        _texture = LoadTexture("resources/paddle.png");
    }

    void MoveX(int direction) 
    {
        if ((_position.x) <= 0) _position.x = 0;
        if ((_position.x + _size.x) >= SCR_WIDTH) _position.x = SCR_WIDTH - _size.x;

        _bounds = Rectangle{ _position.x, _position.y, _size.x, _size.y };

        _position.x += _speed.x * direction;
    }

    void GetDamage() 
    {
        _lifes--;
    }

    void ResetLifes()
    {
        _lifes = 5;
    }

    void DeleteTexture() {
        UnloadTexture(_texture);
    }
};

#endif