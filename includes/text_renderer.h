#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <deque>

class TextRenderer
{
public:
    struct RenderText
    {
        int id;
        std::string text;
        SDL_Color color;
        SDL_Texture* texture;
        SDL_Rect rect;
    };

    static TextRenderer& Instance();

    unsigned int AddText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, TTF_Font* font);
    void UpdateText(int id, SDL_Renderer* renderer, const std::string& newText, TTF_Font* font, SDL_Color color);
    void Draw(SDL_Renderer* renderer);
    void DeleteText(int id);
    void Clear();

private:
    TextRenderer();
    ~TextRenderer();

    TextRenderer(const TextRenderer&) = delete;
    TextRenderer& operator=(const TextRenderer&) = delete;

    std::deque<RenderText> texts;
    int nextId;
};