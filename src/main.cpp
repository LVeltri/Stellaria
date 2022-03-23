#include "Engine.hpp"
#include "Star.hpp"

using namespace std;

Engine *engine = NULL;

int main(int argc, char **args){

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;


    engine = new Engine();
    engine->init("Stellaria", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    while(engine->isRunning()){

        frameStart = SDL_GetTicks();

        engine->handleEvents();
        engine->update();
        engine->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    engine->clean();
    return 0;
}