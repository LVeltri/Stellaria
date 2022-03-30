#include <iostream>
#include <cmath>
#include <fstream>
#include <sndfile.h>
#include <sndfile.hh>

using namespace std;

#define M_PI 3.1415926535

const int sampleRate = 44100;
const int bitDepth = 16;

class SineOscillator {
    float frequency, amplitude, angle = 0.0f, offset = 0.0f;
    fstream file;
public:
    SineOscillator(float freq, float amp) : frequency(freq), amplitude(amp) {
        offset = 2 * M_PI * frequency / sampleRate;
    }
    float process() {
        auto sample = amplitude/2 * (sin(angle) + sin(angle * 0.5));
        angle += offset;
        return sample;
        // Asin(2pif/sr)
    }

    void writeToFile(int value, int size){
        file.write(reinterpret_cast<const char*> (&value), size);
    }

    void create_file(string filename, int duration){
        file.open(filename, ios:binary);

        // Header chunk
        file << "RIFF";
        file << "----";
        file << "WAVE";

        // format chunk
        file << "fmt ";
        writeToFile(16, 4); // Size
        writeToFile(1, 2); // Compression code
        writeToFile(1, 2); // Number of channels
        writeToFile(sampleRate, 4); // Sample rate
        writeToFile(sampleRate * bitDepth / 8, 4 ); // Byte rate
        writeToFile(bitDepth / 8, 2); // Block align
        writeToFile(bitDepth, 2); // Bit depth

        // Data chunk
        file << "data";
        file << "----";

        int preAudioPosition = file.tellp();

        auto maxAmplitude = pow(2, bitDepth - 1) - 1;
        for(int i = 0; i < sampleRate * duration; i++){
            auto sample = process();
            int intSample = static_cast<int> (sample * maxAmplitude);
            writeToFile(intSample, 2);
        }

        int postAudioPosition = file.tellp();

        file.seekp(preAudioPosition - 4);
        writeToFile(postAudioPosition - preAudioPosition, 4);

        file.seekp(4, ios::beg);
        writeToFile(postAudioPosition - 8, 4);

        file.close();

    }

};

static void read_file(const char* filename){
    static short buffer[1024];
    SndfileHandle file;

    file = SndfileHandle(filename);

    printf("opening file: %s", filename);
    
    file.read(buffer, 1024);
    puts("");

}

int main() {
    int duration = 2;
    ofstream audioFile;
    audioFile.open("waveform.wav", ios::binary);
    SineOscillator sineOscillator(243,0.5);

    // Opening and reading file with libsndfile

    read_file("waveform.wav");

    return 0;
}