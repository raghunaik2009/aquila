#include <iostream>
#include "../utils.h"
#include "aquila/WaveFile.h"
#include "aquila/ConsoleProcessingIndicator.h"
#include "aquila/feature/MfccExtractor.h"
#include "aquila/dtw/Dtw.h"

Aquila::Extractor* readIntoExtractor(const std::string& filename)
{
    Aquila::WaveFile wav(20, 0.66);
    wav.load(filename);
    Aquila::Extractor* extractor = new Aquila::MfccExtractor(20, 10);
    Aquila::TransformOptions options;
    options.preemphasisFactor = 0.9375;
    options.windowType = Aquila::WIN_HAMMING;
    options.zeroPaddedLength = wav.getSamplesPerFrameZP();
    Aquila::ConsoleProcessingIndicator cpi;
    extractor->setProcessingIndicator(&cpi);

    std::cout << "Extracting MFCC features from file " << filename << "...\n";
    extractor->process(&wav, options);

    return extractor;
}


int main(int argc, char *argv[])
{
    Aquila::Extractor* from = readIntoExtractor(getFile("test.wav"));
    Aquila::Extractor* to = readIntoExtractor(getFile("test2.wav"));

    std::cout << "Calculating DTW distance..." << std::endl;
    Aquila::Dtw dtw(from);
    double distance = dtw.getDistance(to);
    std::cout << "Finished, distance = " << distance << std::endl;

    delete to;
    delete from;

    std::cin.get();
    return 0;
}
