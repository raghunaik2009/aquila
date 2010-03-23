#include <iostream>
#include "../utils.h"
#include "aquila/WaveFile.h"

int main(int argc, char *argv[])
{
    std::string filename = getFile("test.wav");
    Aquila::WaveFile wav;
    wav.load(filename);
    std::cout << "Filename: "           << wav.getFilename();
    std::cout << "\nLength: "           << wav.getAudioLength()     << " ms";
    std::cout << "\nSample frequency: " << wav.getSampleFrequency() << " Hz";
    std::cout << "\nChannels: "         << wav.getChannelsNum();
    std::cout << "\nByte rate: "        << wav.getBytesPerSec()/1024 << " kB/s";
    std::cout << "\nBits per sample: "  << wav.getBitsPerSamp() << "b\n";

    std::cin.get();
    return 0;
}
