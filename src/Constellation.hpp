#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <ctime>
#include <thread>
#include <chrono>

#include "Star.hpp"
#include "Engine.hpp"

class Constellation{
    public:
        Constellation();
        Constellation(int nbStar, std::string filename, std::string name);
        ~Constellation();

        void load(std::string filename);
        void render();
        void setStar(int index, int x, int y);
        void update();
        void free();
        void checkLimit();
        void border();
        bool inside();
        bool checkStar(int pos);
        void read();
        void selectAll();
        void deselect();
        int posToFreq(int pos);
        void changePosition();
        void printDatas();
        // Get the index of the minimum X star
        void getIndex();
        //Move constellation
        void moveConstellation(int x, int y);
        void changeColor(Uint8 red, Uint8 green, Uint8 blue);
        //Convert angleHoraire en ascencion droite
        void convertAhToAD();
        // 
        void getAhCoordinate();
        void Size(int size);

        std::string getName();

    private:
        int m_nbStar;
        Star *m_star;
        std::string m_file;
        std::string m_name;
        bool selected = false;
        // Boolean used to redefine limits
        bool moved = false;
        bool reading;
        //border
        int m_xMin = 1200, m_xMax = 0, m_yMin = 600, m_yMax = 0;
        int minXDetected, minYDetected, maxXDetected, maxYDetected;
        int margin = 5;
        int xMouse, yMouse;
        int *buffer;
        int angleAH;
};
#endif