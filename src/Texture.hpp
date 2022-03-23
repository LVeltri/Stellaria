#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Engine.hpp"

class Texture{
    public:
        Texture();
        ~Texture();
        bool renderText(std::string textureText, SDL_Color textColor );
        void free();

        void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        int getWidth();
        int getHeight();

        
    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
};