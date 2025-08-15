#include "debug.h"
#include "SDL2/SDL.h"
#include <string>

using namespace std;

void DrawDebug(SDL_Renderer* renderer, int ww, int wh)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, ww - 250, 0, ww - 250, wh);
}