
#include "Benchmark.h"

#include "aquila/dtw/Dtw.h"
#include "aquila/Transform.h"
#include "aquila/WaveFile.h"
#include "aquila/ConsoleProcessingIndicator.h"
#include "../utils.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <boost/filesystem.hpp>
#include <boost/progress.hpp>


Benchmark::Benchmark(int iterations_count):
    ITERATIONS(iterations_count), extractor(0)
{
    std::srand(std::time(0));
}

Benchmark::~Benchmark()
{
    delete extractor;
}

void Benchmark::run()
{
    std::cout << "Benchmarking, please wait..." << std::endl;
    testFft();
    testDct();
    testWavefile();
    testEnergy();
    testMfcc();
    testDtw();

    double result = std::accumulate(durations.begin(), durations.end(), 0.0);
    std::cout << "Benchmarking finished." << std::endl;
    std::cout  << "Total result: " << result << std::endl;
}

void Benchmark::testFft()
{
    const int TEST_DATA_SIZE = 65536;
    std::vector<double> testData(TEST_DATA_SIZE);
    std::generate(testData.begin(), testData.end(), generateRandomDouble);
    Aquila::spectrumType spectrum(TEST_DATA_SIZE);
    Aquila::Transform transform(0);

    boost::progress_display progress(ITERATIONS);
    startTime = clock();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        transform.fft(testData, spectrum);
        ++progress;
    }

    double duration = clock() - startTime;
    durations.push_back(duration);
    std::cout << "FFT: " << duration << std::endl;
}

void Benchmark::testDct()
{
    const int TEST_DATA_SIZE = 1024, DCT_SIZE = 12;
    std::vector<double> testData(TEST_DATA_SIZE), dctOutput(DCT_SIZE);
    std::generate(testData.begin(), testData.end(), generateRandomDouble);
    Aquila::Transform transform(0);

    boost::progress_display progress(ITERATIONS);
    startTime = clock();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        transform.dct(testData, dctOutput);
        ++progress;
    }

    double duration = clock() - startTime;
    durations.push_back(duration);
    std::cout << "DCT: " << duration << std::endl;
}

void Benchmark::testWavefile()
{
    Aquila::WaveFile* wav = new Aquila::WaveFile(20, 0.66);
    std::string filename = getFile("test.wav");

    boost::progress_display progress(ITERATIONS);
    startTime = clock();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        wav->load(filename);
        ++progress;
    }

    double duration = clock() - startTime;
    durations.push_back(duration);
    std::cout << "Wave file: " << duration << std::endl;
    delete wav;
}

void Benchmark::testEnergy()
{
    Aquila::WaveFile* wav = new Aquila::WaveFile(20, 0.66);
    std::string filename = getFile("test.wav");
    wav->load(filename);

    Aquila::Transform transform(0);
    double energy;

    boost::progress_display progress(ITERATIONS);
    startTime = clock();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        for (unsigned int j = 0, fc = wav->getFramesCount(); j < fc; ++j)
        {
            energy = transform.frameLogEnergy(wav->frames[j]);
        }
        ++progress;
    }

    double duration = clock() - startTime;
    durations.push_back(duration);
    std::cout << "Energy: " << duration << std::endl;
    delete wav;
}

void Benchmark::testMfcc()
{
    Aquila::WaveFile* wav = new Aquila::WaveFile(20, 0.66);
    std::string filename = getFile("test.wav");
    wav->load(filename);

    delete extractor;
    extractor = new Aquila::MfccExtractor(20, 10);

    Aquila::TransformOptions options;
    options.preemphasisFactor = 0.9375;
    options.windowType = Aquila::WIN_HAMMING;
    options.zeroPaddedLength = wav->getSamplesPerFrameZP();

    Aquila::ConsoleProcessingIndicator progress;
    extractor->setProcessingIndicator(&progress);

    startTime = clock();
    extractor->process(wav, options);

    double duration = clock() - startTime;
    durations.push_back(duration);
    std::cout << "MFCC: " << duration << std::endl;
    delete wav;
}

void Benchmark::testDtw()
{
    if (!extractor)
        return;

    startTime = clock();
    Aquila::Dtw* dtw = new Aquila::Dtw(extractor);
    dtw->getDistance(extractor);

    double duration = clock() - startTime;
    durations.push_back(duration);
    std::cout << "DTW: " << duration << std::endl;
    delete dtw;
}


double Benchmark::clock()
{
    return t.elapsed();
}


double generateRandomDouble()
{
    return 255.0 * std::rand() / double(RAND_MAX);
}
