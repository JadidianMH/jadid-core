#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "component.h"
#include "sprite_renderer.h"
#include "debug.h"

class GameObject
{
private:
    std::vector<Component*> components;
    std::string nameGameObject;
    static std::vector<GameObject*> allGameObjects;

public:
    GameObject(const std::string& name);
    ~GameObject();

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        T* comp = new T(this, std::forward<Args>(args)...);
        components.push_back(comp);
        AddLog("Added component to " + nameGameObject + ".");
        return comp;
    }

    template <typename T>
    T* GetComponent() {
        for (auto comp : components)
            if (T* casted = dynamic_cast<T*>(comp))
                return casted;
        return nullptr;
    }

    static const std::vector<GameObject*>& GetAllGameObjects() { return allGameObjects; }
    static void RegisterGameObject(GameObject* go);
};