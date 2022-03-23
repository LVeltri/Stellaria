#include "Texture.hpp"

Texture::Texture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture(){
    free();
}

void Texture::free(){
    if(mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
bool Texture::renderText(std::string textureText, SDL_Color textColor){
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(Engine::mainFont, textureText.c_str(), textColor);
    if(textSurface != NULL){
        mTexture = SDL_CreateTextureFromSurface(Engine::renderer, textSurface);
        if(mTexture != NULL){
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }else{
            std::cout << "Unable to create texture !" << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(textSurface);
    }else{
        std::cout << "Unable to render texture: "<< TTF_GetError() << std::endl;
    }

    return mTexture != NULL;
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect renderquad = {x, y, mWidth, mHeight};

    if(clip != NULL){
        renderquad.w = clip->w;
        renderquad.h = clip->h;
    }

    SDL_RenderCopyEx(Engine::renderer, mTexture, clip, &renderquad, angle, center, flip);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}