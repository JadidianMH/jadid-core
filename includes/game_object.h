#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "component.h"
#include "sprite_renderer.h"
#include "debug.h"
#include <SDL2/SDL.h>

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

    static void RenderAllSprites(SDL_Renderer* renderer) {
        std::vector<GameObject*> renderableObjects;
        for (auto go : allGameObjects)
            if (go->GetComponent<SpriteRenderer>())
                renderableObjects.push_back(go);

        std::sort(renderableObjects.begin(), renderableObjects.end(),
                  [](GameObject* a, GameObject* b) {
                      return a->GetComponent<SpriteRenderer>()->zIndex <
                             b->GetComponent<SpriteRenderer>()->zIndex;
                  });

        for (auto go : renderableObjects)
            go->GetComponent<SpriteRenderer>()->Render(renderer);
    }

    static const std::vector<GameObject*>& GetAllGameObjects() { return allGameObjects; }
};
