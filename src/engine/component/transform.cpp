#include "transform.h"


void transform::move(const Vector2& distance)
{
    x += distance.x;
    y += distance.y;
}

void transform::rotate(const int& angle)
{
    rotation = angle;
}

void transform::scale(const Vector2& size)
{
    sx = size.x;
    sy = size.y;
}

void transform::setPosition(const Vector2& position)
{
    x = position.x;
    y = position.y;
}

Vector2 transform::getPosition() const
{
    return {x, y};
}

Vector2 transform::getScale() const
{
    return {sx, sy};
}

int transform::getRotation() const
{
    return rotation;
}