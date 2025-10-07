#pragma once
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>
#include <deque>

struct LogEntry {
    std::string text;
    SDL_Texture* texture;
    int width;
    int height;
};

extern std::deque<LogEntry> logs;

void DrawDebug(SDL_Renderer* renderer, size_t setMaxLogs, TTF_Font* font);
void AddLog(const std::string& message);
void ClearLogs();
