#include "transform.h"


void Transform::move(const Vector2& distance)
{
    x += distance.x;
    y += distance.y;
}

void Transform::rotate(const int& angle)
{
    rotation = angle;
}

void Transform::scale(const Vector2& size)
{
    sx = size.x;
    sy = size.y;
}

void Transform::setPosition(const Vector2& position)
{
    x = position.x;
    y = position.y;
}

Vector2 Transform::getPosition() const
{
    return {x, y};
}

Vector2 Transform::getScale() const
{
    return {sx, sy};
}

int Transform::getRotation() const
{
    return rotation;
}