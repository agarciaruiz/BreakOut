#ifndef BRICK_H
#define BRICK_H

#define BRICKS_LINES             5
#define BRICKS_PER_LINE         20

#include "raylib.h"

class Brick {
private:
    Vector2 _position;
    Vector2 _size;
    Rectangle _bounds;
    int _resistance;
    bool _active;
    Texture2D _texture;

public:
    Vector2 Position() const { return _position; }
    Vector2 Size() const { return _size; }
    Rectangle Bounds() const { return _bounds; }
    int Resistance() const { return _resistance; }
    bool Active() const { return _active; }
    Texture2D Texture() const { return _texture; }

    void Init(Vector2 position, Vector2 size, Rectangle bounds, bool active, Texture2D texture)
    {
        this->_position = position;
        this->_size = size;
        this->_bounds = bounds;
        this->_active = active;
        this->_texture = texture;
    }

    void Destroy()
    {
        _active = false;
    }

    void DeleteTexture() {
        UnloadTexture(_texture);
    }
};
#endif // !BRICK_H