#include <iostream>
#include <boost/timer.hpp>

int main(int argc, char *argv[])
{
    std::cout << "Benchmarking..." << std::endl;
    boost::timer t;
    std::cout << "Minimum elapsed time: " << t.elapsed_min() << std::endl;
    std::cout << "Maximum elapsed time: " << t.elapsed_max() << std::endl;

    std::cout << "Press Enter to leave benchmark...";
    std::cin.get();
    return 0;
}
