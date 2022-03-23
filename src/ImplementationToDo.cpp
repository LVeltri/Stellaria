#include <cmath>
#include <iostream>

//Piano midi Range 21 -> 108

float midiToFreq(int midiNote){
    float freq = 440.f * pow(2.0, ( ( (float)midiNote - 69) / 12) );
    return freq;
}

int scaleTonArray[2][7] = 
{
    {2,2,1,2,2,2,1},
    {2,1,2,2,1,2,2}
};

int* applyScale(int midiNote, int **scale){
    int *newScale;
    for(int i = 0; i < 7; i++){
        newScale[i] = midiNote + scale[0][i];
    }
    return newScale;
}

using namespace std;

int main(){

    for(int i = 0; i < 7; i++){
        cout << scaleTonArray[0][i];
    }cout << endl;

    return 0;
}