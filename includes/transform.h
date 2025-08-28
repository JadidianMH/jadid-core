#pragma once
#include "component.h"

struct Vector2
{
    float x;
    float y;
};

class transform : public Component {
public:
    transform(GameObject* go) : Component(go) {}
private:
    // position on the screen
    float x = 0, y= 0;

    // rotation
    int rotation;

    // x and y scales
    float sx = 1, sy = 1;
public:
    // sum of the current position and the given values
    void move(const Vector2& distance);

    void setPosition(const Vector2& position);

    void scale(const Vector2& Size);

    void rotate(const int& angle);

    Vector2 getPosition() const;

    Vector2 getScale() const;

    int getRotation() const;

};