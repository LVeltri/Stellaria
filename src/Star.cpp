#include "Star.hpp"

Star::Star()
{}

Star::Star(int x, int y, int size)
{
    m_x = x;
    m_y = y;
    m_size = size;
}

Star::~Star(){
    free();
}

int Star::getX(){
    return m_x;
}

int Star::getY(){
    return m_y;
}

void Star::setCoordinates(int x, int y){
    m_x = x;
    m_y = y;
}

void Star::free(){
    m_x = 0;
    m_y = 0;
    drawing = false;
}

void Star::draw(){
    SDL_SetRenderDrawColor(Engine::renderer, m_red, m_green, m_blue, 255);    
    SDL_RenderDrawPoint(Engine::renderer, m_x, m_y);
}

void Star::state(){
    std::cout << getX() << " " << getY() << std::endl;
}

void Star::move(int x, int y){
    m_x += x;
    m_y += y;

    if(m_x > Engine::mWidth){
        m_x = 0;
    }else if(m_x < 0){
        m_x = Engine::mWidth;
    }
    if(m_y > Engine::mHeight){
        m_y = 0;
    }else if(m_y < 0){
        m_y = Engine::mHeight;
    }
}

void Star::printCoordinates(){
    std::cout << "Position: " << m_x << m_y << std::endl;
}

void Star::changeColor(Uint8 red, Uint8 green, Uint8 blue){
    m_red = red;
    m_green = green;
    m_blue = blue;
}