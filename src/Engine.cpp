#include "Engine.hpp"
#include "Star.hpp"
#include "Constellation.hpp"
#include "Texture.hpp"
#include "TimeCalc.hpp"
#include <SDL2/SDL_ttf.h>

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
SDL_Event Engine::e;

Constellation *andr, *ant, *apus, *ara, *ari, *aql, *aqr, *aur;
Constellation *boo;
Constellation *cae, *cam, *cap, *car, *cas, *cen, *cep, *cet, *cha;
Constellation *cir, *cma, *cmi, *cnc, *col, *com, *cra, *crb, *crt, *cru, *crv, *cvn, *cyg;
Constellation *delp, *dor, *dra;
Constellation *equ, *eri;
Constellation *forn;
Constellation *gem, *gru;
Constellation *her, *hor, *hya, *hyi;
Constellation *ind;
Constellation *lac, *leo, *lep, *lib, *lmi, *lup, *lyn, *lyr;
Constellation *men, *mic, *mon, *mus;
Constellation *nor;
Constellation *oct, *oph, *ori;
Constellation *pav, *peg, *per, *phe, *pic, *psa, *psc, *pup, *pyx;
Constellation *ret;
Constellation *scl, *sco, *sct, *ser, *sex, *sge, *sgr;
Constellation *tau, *tel, *tra, *tri, *tuc;
Constellation *uma, *umi;
Constellation *vel, *vir, *vol, *vul; 

//Declare Texture
Texture stellariaText;
Texture dateTexture;
Texture timeTexture;
Texture mousePosition;
Texture playTexture;
Texture sideralTimeTexture;

Engine::Engine(){}

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

    andr = new Constellation(5, "datas/andDatas.star", "andromeda");
    ant = new Constellation(4, "datas/antDatas.star", "antlia");
    apus = new Constellation(4, "datas/apsDatas.star", "apus");
    aql = new Constellation(11, "datas/aqlDatas.star", "aquilae");
    aqr = new Constellation(8, "datas/aqrDatas.star", "aquarius");
    ara = new Constellation(8, "datas/araDatas.star", "ara");
    ari = new Constellation(4, "datas/ariDatas.star", "aries");
    aur = new Constellation(7, "datas/aurDatas.star", "auriga");
    boo = new Constellation(8, "datas/booDatas.star", "bootes");
    cae = new Constellation(4, "datas/caeDatas.star", "caelum");
    cam = new Constellation(5, "datas/camDatas.star", "camelopardalis");
    cap = new Constellation(9, "datas/capDatas.star", "capricornus");
    car = new Constellation(8, "datas/carDatas.star", "carina");
    cas = new Constellation(5, "datas/casDatas.star", "cassiopea");
    cen = new Constellation(16, "datas/cen.star", "centauri");
    cep = new Constellation(10, "datas/cep.star", "cepheus");
    cet = new Constellation(12, "datas/cet.star", "cetus");
    cha = new Constellation(5, "datas/cha.star", "chamaeleon");
    cir = new Constellation(4, "datas/cir.star", "circinus");
    cma = new Constellation(9, "datas/cma.star", "canis major");
    cmi = new Constellation(3, "datas/cmi.star", "canis minor");
    cnc = new Constellation(5, "datas/cnc.star", "cancer");
    col = new Constellation(6, "datas/col.star", "columba");
    com = new Constellation(3, "datas/com.star", "coma berenices");
    cra = new Constellation(10, "datas/cra.star", "corona australis");
    crb = new Constellation(7, "datas/crb.star", "corona borealis");
    crt = new Constellation(8, "datas/crt.star", "crater");
    cru = new Constellation(4, "datas/cru.star", "crux");
    crv = new Constellation(5, "datas/crv.star", "corvus");
    cvn = new Constellation(2, "datas/cvn.star", "canes venatici");
    cyg = new Constellation(10, "datas/cyg.star", "cygnus");
    delp = new Constellation(5, "datas/delDatas.star", "delphinus");
    dor = new Constellation(6, "datas/dor.star", "dorado");
    dra = new Constellation(14, "datas/dra.star", "draconis");
    equ = new Constellation(4, "datas/equ.star", "equuleus");
    eri = new Constellation(30, "datas/eri.star", "eridanus");
    forn = new Constellation(4, "datas/for.star", "fornax");
    gem = new Constellation(17, "datas/gemDatas.star", "gemini");
    gru = new Constellation(8, "datas/gru.star", "grus");
    her = new Constellation(21, "datas/her.star", "hercules");
    hor = new Constellation(6, "datas/hor.star", "horologium");
    hya = new Constellation(17, "datas/hya.star", "hydra");
    hyi = new Constellation(5, "datas/hyi.star", "hydrus");
    ind = new Constellation(5, "datas/ind.star", "indus");
    lac = new Constellation(7, "datas/lac.star", "lacerta");
    leo = new Constellation(9, "datas/leo.star", "leo");
    lep = new Constellation(11, "datas/lep.star", "lepus");
    lib = new Constellation(6, "datas/lib.star", "libra");
    lmi = new Constellation(5, "datas/lmi.star", "leo minor");
    lup = new Constellation(11, "datas/lup.star", "lupus");
    lyn = new Constellation(8, "datas/lyn.star", "lynx");
    lyr = new Constellation(6, "datas/lyr.star", "lyre");
    men = new Constellation(4, "datas/men.star", "mensa");
    mic = new Constellation(5, "datas/mic.star", "microscopium");
    mon = new Constellation(9, "datas/mon.star", "monoceros");
    mus = new Constellation(6, "datas/mus.star", "musca");
    ori = new Constellation(12, "datas/oriDatas.star", "orion");
    uma = new Constellation(7, "datas/umaDatas.star", "ursa major");
    umi = new Constellation(7, "datas/umiDatas.star", "ursa minor");

    //Load font
    mainFont = TTF_OpenFont("res/angelina.ttf", 24);
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
    }else if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
            case SDLK_SPACE:
                if(!reader){
                    reader = true;}
                else reader = false;
                break;
            case SDLK_ESCAPE:
                system("cls");
                break;     
        }
    }
    else if(event.type == SDL_MOUSEMOTION){
        SDL_GetMouseState(&xMouse, &yMouse);
    }else if(event.type == SDL_MOUSEBUTTONUP){
            andr->inside();
            apus->inside();
            ant->inside();
            aql->inside();
            aqr->inside();
            ara->inside();
            ari->inside();
            aur->inside();
            boo->inside();
            cae->inside();
            cam->inside();
            cap->inside();
            car->inside();
            cas->inside();
            cen->inside();
            cep->inside();
            cet->inside();
            cha->inside();
            cir->inside();
            cma->inside();
            cmi->inside();
            cnc->inside();
            col->inside();
            com->inside();
            cra->inside();
            crb->inside();
            crt->inside();
            cru->inside();
            crv->inside();
            cvn->inside();
            cyg->inside();
            delp->inside();
            dor->inside();
            dra->inside();
            equ->inside();
            eri->inside();
            forn->inside();
            gem->inside();
            gru->inside();
            her->inside();
            hor->inside();
            hya->inside();
            hyi->inside();
            ind->inside();
            lac->inside();
            leo->inside();
            lep->inside();
            lib->inside();
            lmi->inside();
            lup->inside();
            lyn->inside();
            lyr->inside();
            men->inside();
            mic->inside();
            mon->inside();
            mus->inside();
            ori->inside();
            uma->inside();
            umi->inside();       
    }else if(event.type == SDL_WINDOWEVENT){
        switch(event.window.event){
            case SDL_WINDOWEVENT_RESIZED:
                mWidth = event.window.data1;
                mHeight = event.window.data2;
                std::cout << "Window resized" << std::endl;
                std::cout << "Dimension:" << mWidth << "x" << mHeight << std::endl;
                break;
        }
    }
}

void Engine::update(){
    time_t t = time(0);
    tm *now = localtime(&t);
    dateNow = std::to_string(now->tm_mday) + "/" +std::to_string(now->tm_mon + 1) + "/" +std::to_string(now->tm_year + 1900);
    timeNow = std::to_string(now->tm_hour) + ":"+std::to_string(now->tm_min) + ":"+ std::to_string(now->tm_sec);
    sideralTimeText = std::to_string(sideralTime(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec,4) );

}

void Engine::render(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    andr->render();
    apus->render();
    ant->render();
    aql->render();
    aqr->render();
    ara->render();
    ari->render();
    aur->render();
    boo->render();
    cae->render();
    cam->render();
    cap->render();
    car->render();
    cas->render();
    cen->render();
    cep->render();
    cet->render();
    cha->render();
    cir->render();
    cma->render();
    cmi->render();
    cnc->render();
    col->render();
    com->render();
    cra->render();
    crb->render();
    crt->render();
    cru->render();
    crv->render();
    cvn->render();
    cyg->render();
    delp->render();
    dor->render();
    dra->render();
    equ->render();
    eri->render();
    forn->render();
    gem->render();
    gru->render();
    her->render();
    hor->render();
    hya->render();
    hyi->render();
    ind->render();
    lac->render();
    leo->render();
    lep->render();
    lib->render();
    lmi->render();
    lup->render();
    lyn->render();
    lyr->render();
    men->render();
    mic->render();
    mon->render();
    mus->render();
    ori->render();
    uma->render();
    umi->render();

    mousePosition.renderText( std::to_string(Engine::xMouse) + " " + std::to_string(Engine::yMouse), {255, 255, 255});
    mousePosition.render(1100,5);

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