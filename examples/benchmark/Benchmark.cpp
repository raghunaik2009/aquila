
#include "Benchmark.h"

#include "aquila/feature/MfccExtractor.h"
#include "aquila/dtw/Dtw.h"
#include "aquila/Transform.h"
#include "aquila/WaveFile.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>

Benchmark::Benchmark(int iterations_count):
    ITERATIONS(iterations_count)
{
    std::srand(std::time(0));
}

void Benchmark::run()
{
    std::cout << "Benchmarking, please wait..." << std::endl;
    testFft();
    testDct();
    //testWavefile();
    //testEnergy();
    //testMfcc();
    //testDtw();

    double result = std::accumulate(durations.begin(), durations.end(), 0.0);
    std::cout << "Benchmarking finished." << std::endl;
    std::cout  << "Total result: " << result << std::endl;
}

void Benchmark::testFft()
{
    startTime = clock();

    const int TEST_DATA_SIZE = 65536;
    std::vector<double> testData(TEST_DATA_SIZE);
    Aquila::spectrumType spectrum(TEST_DATA_SIZE);
    Aquila::Transform transform(0);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        std::generate(testData.begin(), testData.end(), generateRandomDouble);
        transform.fft(testData, spectrum);
    }

    double duration = clock() - startTime;
    durations.push_back(duration);
    std::cout << "FFT: " << duration << std::endl;
}

void Benchmark::testDct()
{
    startTime = clock();

    const int TEST_DATA_SIZE = 1024, DCT_SIZE = 12;
    std::vector<double> testData(TEST_DATA_SIZE), dctOutput(DCT_SIZE);
    Aquila::Transform transform(0);
    for (int i = 0; i < ITERATIONS; ++i)
    {
        std::generate(testData.begin(), testData.end(), generateRandomDouble);
        transform.dct(testData, dctOutput);
    }

    double duration = clock() - startTime;
    durations.push_back(duration);
    std::cout << "DCT: " << duration << std::endl;
}

//void Benchmark::testWavefile()
//{
//    startTime = clock();
//
//    Aquila::WaveFile* wav = new Aquila::WaveFile(20, 0.66);
//    QString filename = SimpleBirdApplication::directoryOf("samples") + "/test.wav";
//    for (int i = 0; i < ITERATIONS; ++i)
//    {
//        wav->load(filename.toStdString());
//    }
//
//    delete wav;
//    double duration = clock() - startTime;
//    durations.push_back(duration);
//    std::cout << "Wave file: " << duration << std::endl;
//}

//void Benchmark::testEnergy()
//{
//    startTime = clock();
//
//    Aquila::WaveFile* wav = new Aquila::WaveFile(20, 0.66);
//    QString filename = SimpleBirdApplication::directoryOf("samples") + "/test.wav";
//    wav->load(filename.toStdString());
//
//    Aquila::Transform transform(0);
//    double energy;
//    for (int i = 0; i < ITERATIONS; ++i)
//    {
//        for (unsigned int j = 0; j < wav->getFramesCount(); ++j)
//        {
//            energy = transform.frameLogEnergy(wav->frames[j]);
//        }
//    }
//
//    delete wav;
//    double duration = clock() - startTime;
//    durations.push_back(duration);
//    std::cout << "Energy: " << duration << std::endl;
//}

//void Benchmark::testMfcc()
//{
//    startTime = clock();
//
//    Aquila::WaveFile* wav = new Aquila::WaveFile(20, 0.66);
//    QString filename = SimpleBirdApplication::directoryOf("samples") + "/test.wav";
//    Aquila::MfccExtractor* extractor = new Aquila::MfccExtractor(20, 10);
//
//    wav->load(filename.toStdString());
//
//    Aquila::TransformOptions options;
//    options.preemphasisFactor = 0.9375;
//    options.windowType = Aquila::WIN_HAMMING;
//    options.zeroPaddedLength = wav->getSamplesPerFrameZP();
//
//    extractor->process(wav, options);
//
//    delete wav;
//    delete extractor;
//    double duration = clock() - startTime;
//    durations.push_back(duration);
//    std::cout << "MFCC: " << duration << std::endl;
//}

//void Benchmark::testDtw()
//{
//    startTime = clock();
//
//    QString fromFile = SimpleBirdApplication::directoryOf("samples") + "/from.bir";
//    QString toFile = SimpleBirdApplication::directoryOf("samples") + "/to.bir";
//    Aquila::Extractor* from = FormatFactory::readIntoExtractor(fromFile);
//    Aquila::Extractor* to = FormatFactory::readIntoExtractor(toFile);
//    Aquila::Dtw* dtw = new Aquila::Dtw(from);
//
//    double distance;
//    for (int i = 0; i < ITERATIONS; ++i)
//    {
//        distance = dtw->getDistance(to);
//    }
//
//    delete dtw;
//    delete to;
//    delete from;
//
//    double duration = clock() - startTime;
//    durations.push_back(duration);
//    std::cout << "DTW: " << duration << std::endl;
//}


double Benchmark::clock()
{
    return t.elapsed();
}


double generateRandomDouble()
{
    return 255.0 * std::rand() / double(RAND_MAX);
}
