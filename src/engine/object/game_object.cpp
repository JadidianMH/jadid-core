#include "game_object.h"

#include "scene.h"
#include "scene_manager.h"

GameObject::GameObject(const std::string& name)
    : nameGameObject(name)
{
    SceneManager::GetActiveScene()->RegisterGameObject(this);
}

GameObject::~GameObject()
{
    for (auto comp : components)
        delete comp;
}

std::string GameObject::GetName() {
    return nameGameObject;
}
