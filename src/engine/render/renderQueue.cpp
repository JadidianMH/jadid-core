#include "renderQueue.h"
#include <algorithm>
#include <iostream>

#include "sprite_renderer.h"
#include "game_object.h"
#include <vector>

std::vector<GameObject*> allGameObjects;

void RegisterGameObject(GameObject* go)
{
    allGameObjects.push_back(go);
}

void RenderAllSprites(SDL_Renderer* renderer)
{
    std::vector<GameObject*> renderableObjects;

    for (GameObject* go : allGameObjects)
    {
        if (go->GetComponent<SpriteRenderer>() != nullptr)
        {
            renderableObjects.push_back(go);
        }
    }

    std::sort(renderableObjects.begin(), renderableObjects.end(),
        [](GameObject* a, GameObject* b) {
            return a->GetComponent<SpriteRenderer>()->zIndex < b->GetComponent<SpriteRenderer>()->zIndex;
        }
    );

    for (GameObject* go : renderableObjects)
    {
        auto sr = go->GetComponent<SpriteRenderer>();
        sr->Render(renderer);
    }
}