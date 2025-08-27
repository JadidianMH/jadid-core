#pragma once
#include <SDL2/SDL.h>
#include <vector>

class GameObject;

void RegisterGameObject(GameObject* go);
void RenderAllSprites(SDL_Renderer* renderer);

extern std::vector<GameObject*> allGameObjects;
