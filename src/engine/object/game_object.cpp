#include "game_object.h"

std::vector<GameObject*> GameObject::allGameObjects;

GameObject::GameObject(const std::string& name)
    : nameGameObject(name)
{
    RegisterGameObject(this);
}

GameObject::~GameObject()
{
    for (auto comp : components)
        delete comp;
}

void GameObject::RegisterGameObject(GameObject* go)
{
    allGameObjects.push_back(go);
}