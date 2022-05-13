#include "Engine.hpp"
#include "Star.hpp"
#include "Constellation.hpp"
#include "Texture.hpp"
#include "TimeCalc.hpp"
#include <iomanip>

//Declare reachable Variable of Engine;
SDL_Renderer* Engine::renderer = nullptr;
TTF_Font *Engine::mainFont = NULL;
bool Engine::reader = false;
int Engine::xMouse;
int Engine::yMouse;
int Engine::mWidth = 1200;
int Engine::mHeight = 600;
int Engine::mTempWidth;
int Engine::mTempHeight;
float Engine::mSideralTime;
SDL_Event Engine::e;

//Declare Texture
Texture stellariaText;
Texture dateTexture;
Texture timeTexture;
Texture mousePosition;
Texture playTexture;
Texture sideralTimeTexture;
Texture constellationName;

const int numberOfConstellation = 88;

Constellation *arrayConstellation[numberOfConstellation] = {
    new Constellation(5, "datas/andDatas.star", "andromeda"),
    new Constellation(4, "datas/antDatas.star", "antlia"),
    new Constellation(4, "datas/apsDatas.star", "apus"),
    new Constellation(11, "datas/aqlDatas.star", "aquilae"),
    new Constellation(8, "datas/aqrDatas.star", "aquarius"),
    new Constellation(8, "datas/araDatas.star", "ara"),
    new Constellation(4, "datas/ariDatas.star", "aries"),
    new Constellation(7, "datas/aurDatas.star", "auriga"),
    new Constellation(8, "datas/booDatas.star", "bootes"),
    new Constellation(4, "datas/caeDatas.star", "caelum"),
    new Constellation(5, "datas/camDatas.star", "camelopardalis"),
    new Constellation(9, "datas/capDatas.star", "capricornus"),
    new Constellation(8, "datas/carDatas.star", "carina"),
    new Constellation(5, "datas/casDatas.star", "cassiopea"),
    new Constellation(16, "datas/cen.star", "centauri"),
    new Constellation(10, "datas/cep.star", "cepheus"),
    new Constellation(12, "datas/cet.star", "cetus"),
    new Constellation(5, "datas/cha.star", "chamaeleon"),
    new Constellation(4, "datas/cir.star", "circinus"),
    new Constellation(9, "datas/cma.star", "canis major"),
    new Constellation(3, "datas/cmi.star", "canis minor"),
    new Constellation(5, "datas/cnc.star", "cancer"),
    new Constellation(6, "datas/col.star", "columba"),
    new Constellation(3, "datas/com.star", "coma berenices"),
    new Constellation(10, "datas/cra.star", "corona australis"),
    new Constellation(7, "datas/crb.star", "corona borealis"),
    new Constellation(8, "datas/crt.star", "crater"),
    new Constellation(4, "datas/cru.star", "crux"),
    new Constellation(5, "datas/crv.star", "corvus"),
    new Constellation(2, "datas/cvn.star", "canes venatici"),
    new Constellation(10, "datas/cyg.star", "cygnus"),
    new Constellation(5, "datas/delDatas.star", "delphinus"),
    new Constellation(6, "datas/dor.star", "dorado"),
    new Constellation(14, "datas/dra.star", "draconis"),
    new Constellation(4, "datas/equ.star", "equuleus"),
    new Constellation(30, "datas/eri.star", "eridanus"),
    new Constellation(4, "datas/for.star", "fornax"),
    new Constellation(17, "datas/gemDatas.star", "gemini"),
    new Constellation(8, "datas/gru.star", "grus"),
    new Constellation(21, "datas/her.star", "hercules"),
    new Constellation(6, "datas/hor.star", "horologium"),
    new Constellation(17, "datas/hya.star", "hydra"),
    new Constellation(5, "datas/hyi.star", "hydrus"),
    new Constellation(5, "datas/ind.star", "indus"),
    new Constellation(7, "datas/lac.star", "lacerta"),
    new Constellation(9, "datas/leo.star", "leo"),
    new Constellation(11, "datas/lep.star", "lepus"),
    new Constellation(6, "datas/lib.star", "libra"),
    new Constellation(5, "datas/lmi.star", "leo minor"),
    new Constellation(11, "datas/lup.star", "lupus"),
    new Constellation(8, "datas/lyn.star", "lynx"),
    new Constellation(6, "datas/lyr.star", "lyre"),
    new Constellation(4, "datas/men.star", "mensa"),
    new Constellation(5, "datas/mic.star", "microscopium"),
    new Constellation(9, "datas/mon.star", "monoceros"),
    new Constellation(6, "datas/mus.star", "musca"),
    new Constellation(4, "datas/nor.star", "norma"),
    new Constellation(4, "datas/oct.star", "octans"),
    new Constellation(12, "datas/oph.star", "ophiucius"),
    new Constellation(12, "datas/oriDatas.star", "orion"),
    new Constellation(7,"datas/pav.star", "pavo"),
    new Constellation(13, "datas/peg.star", "pegasus"),
    new Constellation(19, "datas/per.star", "perseus"),
    new Constellation(7, "datas/phe.star", "phoenix"),
    new Constellation(3, "datas/pic.star", "pictor"),
    new Constellation(7, "datas/psa.star", "pisces austrinus"),
    new Constellation(21, "datas/psc.star", "pisces"),
    new Constellation(9, "datas/pup.star", "puppis"),
    new Constellation(6, "datas/pyx.star", "pyx"),
    new Constellation(7, "datas/ret.star", "reticulum"),
    new Constellation(6, "datas/scl.star", "sculptor"),
    new Constellation(15, "datas/sco.star", "scorpius"),
    new Constellation(6, "datas/sct.star", "scutum"),
    new Constellation(12, "datas/ser.star", "serpens"),
    new Constellation(4, "datas/sex.star", "sextans"),
    new Constellation(5, "datas/sge.star", "sagitta"),
    new Constellation(13, "datas/sgr.star", "sagittarius"),
    new Constellation(14, "datas/tau.star", "taurus"),
    new Constellation(5, "datas/tel.star", "telescopium"),
    new Constellation(3, "datas/tra.star", "triangulum australe"),
    new Constellation(3, "datas/tri.star", "triangulum"),
    new Constellation(6, "datas/tuc.star", "tucana"),
    new Constellation(7, "datas/umaDatas.star", "ursa major"),
    new Constellation(7, "datas/umiDatas.star", "ursa minor"),
    new Constellation(8, "datas/vel.star", "vela"),
    new Constellation(9, "datas/vir.star", "virgo"),
    new Constellation(6, "datas/vol.star", "volans"),
    new Constellation(6, "datas/vul.star", "vulpecula")
    };

Engine::Engine()
{}

void Engine::init(const char* title, int x, int y, int width, int height, Uint32 flags){
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        running = true;  
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        if(window){
            std::cout << "window created" << std::endl;
        }else{
            std::cout << SDL_GetError() << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer == 0){
            // std::cout << "render created" << std::endl;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }else{
            std::cout << SDL_GetError() << std::endl;
        }
    }
    // Init TTF()
    if(TTF_Init() == -1){
        std::cout << "SDL could not init ! " << TTF_GetError() << std::endl; 
    }

    //Load font
    mainFont = TTF_OpenFont("res/Roboto-Regular.ttf", 20);
    if(mainFont == NULL){
        std::cout << "Failed to load font" << TTF_GetError() << std::endl;
    }else{
        SDL_Color textColor = {255, 255, 0};
        if(!stellariaText.renderText("Stellaria", textColor) ){
            std::cout << "Failed to render texture" << std::endl;
        }
    }
}

void Engine::clean(){

    stellariaText.free();

    for(int i = 0; i < numberOfConstellation; i++){
        arrayConstellation[i]->free();
    }

    TTF_CloseFont(mainFont);
    mainFont = NULL;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    TTF_Quit();
    SDL_Quit();
}

void Engine::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);

    if(event.type == SDL_QUIT){
        running = false;
    }else if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_SPACE:
                if(!reader){
                    reader = true;
                    }
                else reader = false;
                break;
                
            case SDLK_ESCAPE:
            for(int i = 0; i < numberOfConstellation; i++){
                arrayConstellation[i]->deselect();
            }
                system("cls");
                readingLine = 0;
                break;
            case SDLK_a:
                for(int i = 0; i < numberOfConstellation; i++){
                    arrayConstellation[i]->selectAll();
                }
                break;
            case SDLK_q:
                running = false;
                break;
            case SDLK_g:
                if(grided == false)
                    grided = true;
                else 
                    grided = false;
                break;

            case SDLK_p:
                readingLine += 1;
                break;
        }
    }
    else if(event.type == SDL_MOUSEMOTION){
        SDL_GetMouseState(&xMouse, &yMouse);
    }else if(event.type == SDL_MOUSEBUTTONUP){
        for(int i = 0; i < numberOfConstellation; i++){
            arrayConstellation[i]->inside();
        }
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN){
        readingLine = xMouse;
    }
    
    else if(event.type == SDL_WINDOWEVENT){
        switch(event.window.event){
            case SDL_WINDOWEVENT_RESIZED:
                mTempWidth = mWidth;
                mTempHeight = mHeight;
                mWidth = event.window.data1;
                mHeight = event.window.data2;
                std::cout << "Window resized" << std::endl;
                std::cout << "Old Dimension:" << mTempWidth << "x" << mTempHeight << std::endl;
                std::cout << "Dimension:" << mWidth << "x" << mHeight << std::endl;

                for(int i = 0; i < numberOfConstellation; i++){
                    arrayConstellation[i]->changePosition();
                }
                break;
        }
    }
}

void Engine::update(){
    time_t t = time(0);
    tm *now = localtime(&t);
    dateNow = std::to_string(now->tm_mday) + "/" +std::to_string(now->tm_mon + 1) + "/" +std::to_string(now->tm_year + 1900);
    timeNow = std::to_string(now->tm_hour) + ":"+std::to_string(now->tm_min) + ":"+ std::to_string(now->tm_sec);
    mSideralTime =  sideralTime(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec,4);
    sideralTimeText = "Temps sideral: " + convertTime2(mSideralTime);

}

void Engine::render(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for(int i = 0; i < numberOfConstellation ; i++){
        arrayConstellation[i]->render();
    }

    convertMousePosition();
   
    mousePosition.render(mWidth - 60 ,5);

    dateTexture.renderText(dateNow, {0, 100, 255} );
    dateTexture.render(20,40);
    timeTexture.renderText(timeNow, {0, 100, 255} );
    timeTexture.render(120,40);
    sideralTimeTexture.renderText(sideralTimeText, {0, 100, 255} );
    sideralTimeTexture.render(20, 60);

    if(reader){
        playTexture.renderText("play", {0,255,0});
    }else{
        playTexture.renderText("pause",{255,0,0});
    }

    playTexture.render(110,20);

    stellariaText.render(20,20);

    // grid();
    
    SDL_RenderPresent(renderer);
}

bool Engine::isRunning(){
    return running;
}

int Engine::getWidth(){
    return mWidth;
}
int Engine::getHeight(){
    return mHeight;
}

void Engine::grid(){
    if(grided){
        SDL_SetRenderDrawColor(Engine::renderer, 0, 122, 255, 0);
        for(int i = 0; i < 24; i++){
            SDL_RenderDrawLine(Engine::renderer, (int)((i * mWidth)/24), 0, (int)((i * mWidth)/24), mHeight );
        }
        for(int i = 0; i < 180; i++){
            SDL_RenderDrawLine(renderer, 0, (int)((i * mHeight) / 180), mWidth, (int)((i * mHeight) / 180)) ;
        }
    }
    else{
        SDL_SetRenderDrawColor(Engine::renderer, 0,0,0,255);
    }
}

void Engine::line(){

    if(reader){
        SDL_SetRenderDrawColor(Engine::renderer, 255, 255, 0, 255);
        SDL_RenderDrawLine(Engine::renderer, readingLine, 0, readingLine, mHeight);
        readingLine += 1;
    }
    if(readingLine > mWidth){
        readingLine = 0;
    }
}

void Engine::convertMousePosition(){
    
    // X position ==> Hour (24->0)
    int hourPos = -(24.0 /  (double)mWidth) * (double)xMouse + 24;
    // Y position ==> Angle (90->-90)
    int anglePos = -(180.0 / (double)mHeight) * (double)yMouse + 90.0;
    // Set mouse position texture
    mousePosition.renderText( std::to_string(hourPos) + " " + std::to_string(anglePos), {255, 255, 255});
}