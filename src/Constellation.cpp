#include "Constellation.hpp"
#include "Engine.hpp"

#include <cmath>

//Init Constellation
Constellation::Constellation()
{}
Constellation::Constellation(int nbStar, std::string filename, std::string name) : m_nbStar(nbStar), m_file(filename), m_name(name)
{
    m_star = new Star[m_nbStar];
    load(m_file);
    border();
}
//Deallocate Constellation
Constellation::~Constellation(){
    free();
}
// Load the constellation file
void Constellation::load(std::string filename){
    //Open the file
    std::ifstream consFile(filename.c_str() );
    if(consFile.fail()){
        std::cout << "Failed to open the file " << filename.c_str() << std::endl;
    }
    int x = -1;
    int y = -1;
    //Assign each star for each coordinates
    for(int star = 0; star < m_nbStar; star++){
        consFile >> x;
        int newX = x;
        consFile >> y;
        int newY = y;

        setStar(star, x, y);
    }
}
//Deallocate the star array
void Constellation::free(){
    for(int i = 0; i < m_nbStar; i++){
        m_star[i].free();
    }
}
//Draw all the star and the border if selected
void Constellation::render(){
    border();
    for(int i = 0; i < m_nbStar; i++){
        m_star[i].draw();
    }

}

// Change Constellation position after resizing
void Constellation::setStar(int index, int x, int y){
    x = (x * Engine::mWidth) / 360;
    y =  (y * (-1) + 90) * Engine::mHeight / 180;
    m_star[index].setCoordinates(x, y);
    m_star[index].setSize(1);
}

//Update the constellation position
void Constellation::update(){
}
// Check the limit of the Constellation
void Constellation::checkLimit(){
    for(int i = 0; i < m_nbStar ; ++i){
        //define x border
        if(m_star[i].getX() < m_xMin){
            m_xMin = m_star[i].getX();
        }
        if(m_star[i].getX() > m_xMax){
            m_xMax = m_star[i].getX();
        }
        //define y border
        if(m_star[i].getY() < m_yMin){
            m_yMin = m_star[i].getY();
        }
        if(m_star[i].getY() > m_yMax){
            m_yMax = m_star[i].getY();
        }
    }
    getIndex();
        m_xMin = m_star[minXDetected].getX();
        m_xMax = m_star[maxXDetected].getX();
        m_yMin = m_star[minYDetected].getY();
        m_yMax = m_star[maxYDetected].getY();
    
}
// Get the index of the minimum X star
void Constellation::getIndex(){
    for(int i = 0; i < m_nbStar; i++){
        if(m_star[i].getX() == m_xMin){
            minXDetected = i;
        }
        if(m_star[i].getX() == m_xMax){
            maxXDetected = i;
        }
        if(m_star[i].getY() == m_yMin){
            minYDetected = i;
        }
        if(m_star[i].getY() == m_yMax){
            maxYDetected = i;
        }
    }
}
// Define and create border
void Constellation::border(){
    checkLimit();
    // White color
    if(!Engine::reader){
       SDL_SetRenderDrawColor(Engine::renderer, 255,255,255,255);
        
    }
    //Change to red color if play activated
    else{
       SDL_SetRenderDrawColor(Engine::renderer, 255,0,0,255);
       read();
    }
    
    //If constellation selected draw border with a little margin
    if(selected){   
        //up
        SDL_RenderDrawLine(Engine::renderer, m_xMin - margin, m_yMin - margin, m_xMax + margin, m_yMin - margin);
        //down
        SDL_RenderDrawLine(Engine::renderer, m_xMin - margin, m_yMax + margin, m_xMax + margin, m_yMax + margin);
        //left
        SDL_RenderDrawLine(Engine::renderer, m_xMin - margin, m_yMin - margin, m_xMin - margin, m_yMax + margin);
        //right
        SDL_RenderDrawLine(Engine::renderer, m_xMax + margin, m_yMin - margin, m_xMax + margin, m_yMax + margin);         
    }
}
// Check if mouse inside
/* Warning !! Some Constellations are inside another Constellation Border!!
Add Function to prevent multiple selection*/
bool Constellation::inside(){
    //If mouse is clicked inside and selected = false turn selected --> true;
    if(Engine::xMouse > m_xMin && Engine::xMouse  < m_xMax && Engine::yMouse > m_yMin && Engine::yMouse < m_yMax && selected == false){
        selected = true;
        std::cout << "Constellation: " << m_name << std::endl;
        changeColor(0,255,0);
        for(int i = 0; i < m_nbStar; i++){
            m_star[i].setSize(2);
        }
        std::cout << "Limit: " << m_xMin << " - " << m_xMax << std::endl;
        read();
    }
    //If mouse is clicked inside and selected = true turn selected --> false;
    else if(Engine::xMouse > m_xMin && Engine::xMouse  < m_xMax && Engine::yMouse > m_yMin && Engine::yMouse < m_yMax && selected == true){
        selected = false;
        changeColor(255,255,255);
        for(int i = 0; i < m_nbStar; i++){
            m_star[i].setSize(1);
        }
    }
}
//Check star position for read method
bool Constellation::checkStar(int pos){
    bool check = false;
    //Loop for all star in the constellation
    for(int i = 0; i < m_nbStar; i++){
        //Get the X position of the star
        if(pos == m_star[i].getX() ){
            //If position = x position of the star indexed i;
            check = true;
        }
    }
    return check;
}
//Read buffer
void Constellation::read(){
    //Create a buffer within the limit of the constellation
    int bufPos;
    int bufferSize = m_xMax - m_xMin;
    bufPos = m_xMin;
    std::cout << "Buffer size: " << bufferSize << std::endl;
    std::cout << "Pos: " << bufPos << std::endl;
    
    while(Engine::reader == true){
        // std::cout << "Reading" << std::endl;
        bufPos += 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // std::cout << bufPos << std::endl;
        // system("cls");
        if(bufPos > m_xMax){
            bufPos = m_xMin;
        }
    }

}
//Convert position to Frequency
int Constellation::posToFreq(int pos){
    int freq;
    //Scale freq to 200 -> 2000 from position 0 to 600 (screen height)
    freq = pos * 1800 / 600 + 200;

    return freq;
}
// Change position if window resized
void Constellation::changePosition(){
    for(int i = 0; i < m_nbStar; i++){
        m_star[i].setCoordinates( 
            (int)(m_star[i].getX() * Engine::getWidth() / Engine::mTempWidth), 
            (int)(m_star[i].getY() * Engine::getHeight() / Engine::mTempHeight) 
        );
    }
}

void Constellation::printDatas(){
    std::cout << m_name << std::endl;
    for(int i = 0; i < m_nbStar; i++){
        std::cout << "Positions: " << m_star[i].getX() << ", " << m_star[i].getY() << std::endl;
    }
    system("cls");
}

void Constellation::moveConstellation(int x, int y){
    for(int i = 0; i < m_nbStar; i++){
        m_star[i].move(x, y);
    }
    moved = true;
}

void Constellation::changeColor(Uint8 red, Uint8 green, Uint8 blue){
    for(int i = 0; i < m_nbStar; i++){
        m_star[i].changeColor(red, green, blue);
    }
}

// AH coordinate : H = T - a
void Constellation::getAhCoordinate(){
        // *Make a for loop to get for each star every X pos and change each X to AH coordinates*//
    for(int i =  0; i < m_nbStar; i++){
        m_star[i].setCoordinates(Engine::mSideralTime - m_star[i].getX(), m_star[i].getY() );
    }
}

void Constellation::Size(int size){
    for(int i = 0; i < m_nbStar; i++){
        m_star[i].setSize(size);
    }
}

std::string Constellation::getName(){
    return m_name;
}

/*=============Function for constellation Array=============*/

// Select all Constellations
void Constellation::selectAll(){
    selected = true;
    changeColor(0,255,150);
    std::cout << "Constellation: " << m_name << std::endl;
        for(int i = 0; i < m_nbStar; i++){
            m_star[i].setSize(2);
        }
}

// Deselect all Constellations
void Constellation::deselect(){
    selected = false;
    changeColor(255,255,255);
        for(int i = 0; i < m_nbStar; i++){
            m_star[i].setSize(1);
        }
}