#include "debug.h"
#include "SDL2/SDL.h"
#include <string>

using namespace std;

void DrawDebug(SDL_Renderer* renderer)
{
    string txt = "sone random text";
    SDL_Rect rect;
    rect.x = 800;
    rect.y = 0;
    rect.w = 200;
    rect.h = 600;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}