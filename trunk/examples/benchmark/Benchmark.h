#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <string>
#include <vector>
#include <boost/timer.hpp>

class Benchmark
{
public:
    Benchmark(int iterations_count);
    void run();

private:
    void testFft();
    void testDct();
    void testWavefile();
    void testEnergy();
    void testMfcc();
    //void testDtw();

    std::string getFile(const std::string& filename);


    double clock();
    boost::timer t;

    int ITERATIONS;

    double startTime;

    std::vector<double> durations;
};

double generateRandomDouble();

#endif // BENCHMARK_H
