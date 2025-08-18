#include "text_renderer.h"
#include "debug.h"

TextRenderer& TextRenderer::Instance()
{
    static TextRenderer instance;
    return instance;
}

TextRenderer::TextRenderer()
    : nextId(1)
{
}

TextRenderer::~TextRenderer()
{
    Clear();
}

unsigned int TextRenderer::AddText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, TTF_Font* font)
{
    RenderText newText{};
    newText.id = nextId++;
    newText.text = text;
    newText.color = color;

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface)
    {
        AddLog("Failed to render text surface");
        return 0;
    }

    newText.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!newText.texture)
    {
        AddLog("Failed to create texture from surface");
        SDL_FreeSurface(surface);
        return 0;
    }

    newText.rect = { x, y, surface->w, surface->h };

    SDL_FreeSurface(surface);

    texts.push_back(std::move(newText));
    return newText.id;
}

void TextRenderer::UpdateText(int id, SDL_Renderer* renderer, const std::string& newText, TTF_Font* font, SDL_Color color)
{
    for (auto& text : texts)
    {
        if (text.id == id)
        {
            SDL_DestroyTexture(text.texture);

            text.text = newText;
            text.color = color;

            SDL_Surface* surface = TTF_RenderText_Blended(font, newText.c_str(), color);
            if (!surface)
            {
                AddLog("Failed to render text surface in UpdateText");
                text.texture = nullptr;
                return;
            }

            text.texture = SDL_CreateTextureFromSurface(renderer, surface);
            text.rect.w = surface->w;
            text.rect.h = surface->h;

            SDL_FreeSurface(surface);
            return;
        }
    }
}

void TextRenderer::Draw(SDL_Renderer* renderer)
{
    for (auto& text : texts)
    {
        SDL_RenderCopy(renderer, text.texture, nullptr, &text.rect);
    }
}

void TextRenderer::DeleteText(int id)
{
    for (auto it = texts.begin(); it != texts.end(); ++it)
    {
        if (it->id == id)
        {
            SDL_DestroyTexture(it->texture);
            texts.erase(it);
            return;
        }
    }
}

void TextRenderer::Clear()
{
    for (auto& text : texts)
    {
        SDL_DestroyTexture(text.texture);
    }
    texts.clear();
}