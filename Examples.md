# Examples #

Following code samples are based on Aquila 2.5.3.

## Read a .wav file and display properties ##

```
#include <iostream>
#include "aquila/WaveFile.h"

int main(int argc, char *argv[])
{
    Aquila::WaveFile wav;
    wav.load("test.wav");
    std::cout << "Filename: "           << wav.getFilename();
    std::cout << "\nLength: "           << wav.getAudioLength()     << " ms";
    std::cout << "\nSample frequency: " << wav.getSampleFrequency() << " Hz";
    std::cout << "\nChannels: "         << wav.getChannelsNum();
    std::cout << "\nByte rate: "        << wav.getBytesPerSec()/1024 << " kB/s";
    std::cout << "\nBits per sample: "  << wav.getBitsPerSamp() << "b\n";
    return 0;
}
```

## MFCC feature extraction ##

```
#include "aquila/feature/WaveFile.h"
#include "aquila/feature/MfccExtractor.h"
#include "aquila/feature/TextFeatureWriter.h"

int main(int argc, char *argv[])
{
    Aquila::WaveFile wav(20, 0.66);
    wav.load("test.wav");
    Aquila::MfccExtractor extractor(20, 10);
    Aquila::TransformOptions options;
    options.preemphasisFactor = 0.9375;
    options.windowType = Aquila::WIN_HAMMING;
    options.zeroPaddedLength = wav.getSamplesPerFrameZP();
    extractor.process(&wav, options);
    Aquila::TextFeatureWriter writer("feature.txt");
    extractor.save(writer);

    return 0;
}
```


### Calculating DTW distance between two recordings ###

```
#include <iostream>
#include <string>
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
    Aquila::Extractor* from = readIntoExtractor("test.wav");
    Aquila::Extractor* to = readIntoExtractor("test2.wav");
    std::cout << "Calculating DTW distance..." << std::endl;
    Aquila::Dtw dtw(from);
    double distance = dtw.getDistance(to);
    std::cout << "Finished, distance = " << distance << std::endl;
    delete to;
    delete from;
    return 0;
}
```