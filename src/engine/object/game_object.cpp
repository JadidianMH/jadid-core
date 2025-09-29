#include "game_object.h"

GameObject::GameObject(const std::string& name)
    : nameGameObject(name)
{
    // RegisterGameObject(this);
}

GameObject::~GameObject()
{
    for (auto comp : components)
        delete comp;
}

std::string GameObject::GetName() {
    return nameGameObject;
}
