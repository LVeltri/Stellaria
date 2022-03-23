#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <ctime>

class Engine{
    public:
    Engine();
    void init(const char* title, int x, int y, int width, int height, Uint32 flags);
    void update();
    void render();
    void clean();

    void handleEvents();

    bool isRunning();

    static SDL_Renderer* renderer;
    static int xMouse;
    static int yMouse;
    static TTF_Font *mainFont;

    static SDL_Event e;

    static int mWidth;
    static int mHeight;
    static int mTempWidth;
    static int mTempHeight;

    std::string dateNow;
    std::string timeNow;
    std::string sideralTimeText;

    static bool reader;

    //Get dimension of the window
    int getWidth();
    int getHeight();

    private:
        bool running;
        SDL_Window* window; 
};

