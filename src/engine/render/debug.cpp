#include "debug.h"
#include <SDL2/SDL_ttf.h>
#include <deque>
#include "SDL2/SDL.h"
#include <string>

using namespace std;


std::deque<LogEntry> logs;
const size_t maxLogs = 6;

void DrawDebug(SDL_Renderer* renderer, int wh, TTF_Font* font)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 250, 0, 250, wh);
    int y = 10;
    SDL_Color color = {255, 255, 255, 255};

    for (auto& log : logs) {
        if (!log.texture) {
            SDL_Surface* surf = TTF_RenderText_Blended(font, log.text.c_str(), color);
            log.texture = SDL_CreateTextureFromSurface(renderer, surf);
            log.height = surf->h;
            log.width = surf->w;
            SDL_FreeSurface(surf);
        }

        SDL_Rect dst = {10, y, log.width, log.height};
        SDL_RenderCopy(renderer, log.texture, nullptr, &dst);

        y += log.height + 2;
    }
}
void AddLog(const std::string& message)
{
    logs.push_back({message});
    if (logs.size() > maxLogs)
    {
        if (logs.front().texture)
        {
            SDL_DestroyTexture(logs.front().texture);
        }
        logs.pop_front();
    }
}
void ClearLogs() {
    for (auto& log : logs) {
        if (log.texture) SDL_DestroyTexture(log.texture);
    }
    logs.clear();
}