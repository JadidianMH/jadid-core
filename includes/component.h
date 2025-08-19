#pragma once

class GameObject;

class Component
{
public:
    GameObject* gameObject;

    Component(GameObject* gameObject) : gameObject(gameObject) {}
    virtual ~Component() {}

    virtual void Update() {}
};