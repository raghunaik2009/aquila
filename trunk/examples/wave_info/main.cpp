#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "aquila/WaveFile.h"

std::string getFile(const std::string &filename)
{
    using namespace boost::filesystem;
    path program_path(initial_path<path>());
    if (program_path.filename() == "debug" ||
        program_path.filename() == "release")
    {
        program_path = program_path.parent_path();
    }
    program_path = program_path.parent_path();
    program_path /= filename;
    return program_path.file_string();
}


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
