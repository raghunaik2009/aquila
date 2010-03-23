#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "aquila/WaveFile.h"
#include "aquila/ConsoleProcessingIndicator.h"
#include "aquila/feature/MfccExtractor.h"
#include "aquila/feature/TextFeatureWriter.h"

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
    Aquila::WaveFile wav(20, 0.66);
    wav.load(filename);
    Aquila::MfccExtractor extractor(20, 10);
    Aquila::TransformOptions options;
    options.preemphasisFactor = 0.9375;
    options.windowType = Aquila::WIN_HAMMING;
    options.zeroPaddedLength = wav.getSamplesPerFrameZP();
    Aquila::ConsoleProcessingIndicator cpi;
    extractor.setProcessingIndicator(&cpi);

    std::cout << "Extracting MFCC features...\n";
    extractor.process(&wav, options);
    Aquila::TextFeatureWriter writer("feature.txt");
    extractor.save(writer);
    std::cout << "Finished!";

    std::cin.get();
    return 0;
}

