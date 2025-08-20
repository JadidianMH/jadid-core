#pragma once
#include "component.h"

struct Vector2
{
    int x;
    int y;
};

class Transform : public Component {
public:
    Transform(GameObject* go) : Component(go) {}
private:
    // position on the screen
    int x, y;

    // rotation
    int rotation;

    // x and y scales
    int sx, sy;
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