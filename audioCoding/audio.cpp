#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

const int sample_rate = 44100;
const int bitDepth = 16;

#ifndef MPI
#define MPI 3.141592653589
#endif

class Sine{
    float frequency, amplitude, angle = 0.0f, offset = 0.0;
    ofstream audioFile;
    public:
        Sine(){};
        Sine(float freq, float amp) : frequency(freq), amplitude(amp){
            offset = 2 * MPI * frequency / sample_rate;
        }
        float process(){
            auto sample =  amplitude * sin(angle);
            angle += offset;
            return sample;
        }
        void write(int duration){

            auto maxAmplitude = pow(2, bitDepth -1) -1;
            for(int i = 0; i < sample_rate * duration; i++){
                auto sample = process();
                int intSample = static_cast<int> (sample * maxAmplitude);
                audioFile.write(reinterpret_cast<char*> (&intSample), 2);  
            }
                    
        }

        void changeFreq(int newFreq){
            offset = 2 * MPI * newFreq / sample_rate;
        }

        int arrDuration[3] = {1,3,2};
        float arrFreq[3] = {261.93, 392.0, 369.99};

        void read(){
            audioFile.open("waveform.wav", ios::binary);
            for(int i = 0; i < 3; i++){
               changeFreq(arrFreq[i]);
               write(arrDuration[i]);
           }
           audioFile.close(); 
        }
};

int main(){

    Sine sine(440,0.2);
    sine.read();

    return 0;
}