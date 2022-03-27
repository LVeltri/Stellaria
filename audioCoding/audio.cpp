#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <portaudio/portaudio.h>

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
        void write(float duration){

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



        void read(float *frequency, float *duration, int size){
            audioFile.open("waveform.wav", ios::binary);
            for(int i = 0; i < size; i++){
               changeFreq(frequency[i]);
               write(duration[i]);
           }
           audioFile.close(); 
        }
};

typedef int PaCallback(const void *input,
                             void *output,
                             unsigned long frameCount,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData);

int main(){

    PaError err;

    err = Pa_Initialize();


    float arrDuration[8] = {0.5,0.25,0.25,0.5,0.25,0.255,0.5,0.25};
    float arrFreq[8] = {261.93, 392.00, 329.63, 392.00, 261.93, 392.00, 329.63, 392.00};

    Sine sine(440,0.2);
    sine.read(arrFreq,arrDuration,8);


    Pa_Terminate();
    return 0;
}