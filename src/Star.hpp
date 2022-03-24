#ifndef STAR_H
#define STAR_H

#include <iostream>
#include <SDL2/SDL.h>
#include <ctime>
#include "Engine.hpp"

class Star{
    public:
        Star();
        Star(int x, int y, int size = 1);
        ~Star();

        int getX();
        int getY();
        void printCoordinates();


        
        void setCoordinates(int x, int y);

        void draw();

        void move(int x, int y);
        
        void free();

        void state();

        void changeColor(Uint8 red, Uint8 green, Uint8 blue);

    private:
        int m_x;
        int m_y;
        int m_size;
        SDL_Rect starRect;
        bool drawing;
        Uint8 m_red = 255, m_green = 255, m_blue = 255; 
};

#endif