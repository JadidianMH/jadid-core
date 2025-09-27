#include "game_object.h"

std::vector<GameObject*> GameObject::allGameObjects;

GameObject::GameObject(const std::string& name)
    : nameGameObject(name)
{
    allGameObjects.push_back(this);
}

GameObject::~GameObject()
{
    for (auto comp : components)
        delete comp;
}