#include "render_queue.h"
#include "game_object.h"
#include "sprite_renderer.h"
#include <algorithm>
#include <vector>

#include "scene_manager.h"

void RenderAllSprites(SDL_Renderer* renderer)
{
    std::vector<GameObject*> renderableObjects;

    for (auto go : SceneManager::GetActiveScene()->GetAllGameObjects())
    {
        if (go->GetComponent<SpriteRenderer>())
            renderableObjects.push_back(go);
    }

    std::sort(renderableObjects.begin(), renderableObjects.end(),
              [](GameObject* a, GameObject* b) {
                  return a->GetComponent<SpriteRenderer>()->zIndex <
                         b->GetComponent<SpriteRenderer>()->zIndex;
              });

    for (auto go : renderableObjects)
        go->GetComponent<SpriteRenderer>()->Render(renderer);
}
