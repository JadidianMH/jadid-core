#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <deque>

class ImageRenderer
{
public:
    struct RenderImage
    {
        int id;
        SDL_Texture* texture;
        SDL_Rect rect;
    };

    static ImageRenderer& Instance();

    unsigned int AddImage(SDL_Renderer* renderer, const std::string& filepath, int x, int y, int w, int h);

    void UpdateImage(int id, SDL_Renderer* renderer, const std::string& filepath, int w, int h);

    void Draw(SDL_Renderer* renderer);

    void DeleteImage(int id);

    void Clear();

private:
    ImageRenderer();
    ~ImageRenderer();

    ImageRenderer(const ImageRenderer&) = delete;
    ImageRenderer& operator=(const ImageRenderer&) = delete;

    std::deque<RenderImage> images;
    int nextId;
};