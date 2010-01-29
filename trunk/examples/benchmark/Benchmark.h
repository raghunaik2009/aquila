#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <vector>
#include <boost/timer.hpp>

class Benchmark
{
public:
    Benchmark();
    void run();

private:
    void testFft();
    void testDct();
    //void testWavefile();
    //void testEnergy();
    //void testMfcc();
    //void testDtw();


    double clock();
    boost::timer t;

    int ITERATIONS;

    double startTime;

    std::vector<double> durations;
};

double generateRandomDouble();

#endif // BENCHMARK_H
