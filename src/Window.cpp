/**
 * @file Window.cpp
 *
 * Window functions - implementation.
 *
 * A signal frame should be multiplied by a time window before processing,
 * to decrease the magnitude of side lobes.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.6.0
 * @since 0.5.4
 */

#include "Window.h"
#include <algorithm>

namespace Aquila
{
    Cache<Window::keyType, double*> Window::windowsCache(Window::createWindow);

    /**
     * Returns window value for a given window type, size and position.
     *
     * Window is first looked up in cache. If it doesn't exist,
     * it is generated. The cached value is then returned.
     *
     * @param type window function type
     * @param n sample position in the window
     * @param N window length
     * @return window value for n-th sample
     */
    double Window::apply(WindowType type, unsigned int n, unsigned int N)
    {
        keyType key = std::make_pair(type, N);
        double* window = windowsCache.get(key);

        return window[n];
    }

    /**
     * Generates new window array for a given type and size.
     *
     * @param windowKey a cache key
     */
    double* Window::createWindow(const keyType& windowKey)
	{
        WindowType type = windowKey.first;
        unsigned int N = windowKey.second;
        double* window = new double[N];
        std::generate_n(window, N, WinGenerator(type, N));

        return window;
	}

    /**
     * Rectangular window.
     *
     * @param n sample position (ignored)
     * @param N window size (ignored)
     * @return n-th window sample value (always 1.0)
     */
    double Window::rectangular(unsigned int, unsigned int)
    {
        return 1.0;
    }

    /**
     * Hamming window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::hamming(unsigned int n, unsigned int N)
    {
        return 0.53836 - 0.46164 * std::cos(2.0 * M_PI * n / double(N - 1));
    }

    /**
     * Hann window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::hann(unsigned int n, unsigned int N)
    {
        return 0.5 * (1.0 - std::cos(2.0 * M_PI * n / double(N - 1)));
    }

    /**
     * Barlett (triangular) window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::barlett(unsigned int n, unsigned int N)
    {
        return 1.0 - (2.0 * std::fabs(n - (N - 1) / 2.0)) / (double(N - 1));
    }

    /**
     * Blackman window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::blackman(unsigned int n, unsigned int N)
    {
        return 0.42 - 0.5 * std::cos(2.0 * M_PI * n / double(N - 1)) +
                0.08 * std::cos(4.0 * M_PI * n / double(N - 1));
    }

    /**
     * Flat-top window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::flattop(unsigned int n, unsigned int N)
    {
        return 1.0 - 1.93 * std::cos(2.0 * M_PI * n / double(N - 1)) +
                1.29 * std::cos(4.0 * M_PI * n / double(N - 1)) -
                0.388 * std::cos(6.0 * M_PI * n / double(N - 1)) +
                0.0322 * std::cos(8.0 * M_PI * n / double(N - 1));
    }

    /**
     * Creates the generator functor.
     *
     * @param type window function type
     * @param N window size
     */
    Window::WinGenerator::WinGenerator(WindowType type, unsigned int N):
        _N(N)
    {
        switch (type)
        {
        case WIN_RECT:
            windowMethod = &Window::rectangular;
            break;
        case WIN_HAMMING:
            windowMethod = &Window::hamming;
            break;
        case WIN_HANN:
            windowMethod = &Window::hann;
            break;
        case WIN_BARLETT:
            windowMethod = &Window::barlett;
            break;
        case WIN_BLACKMAN:
            windowMethod = &Window::blackman;
            break;
        case WIN_FLATTOP:
            windowMethod = &Window::flattop;
            break;
        default:
            windowMethod = &Window::hamming;
            break;
        }
    }

    /**
     * Calculates next window sample.
     *
     * Each consecutive call will advance position by one sample.
     *
     * @return window sample
     */
    double Window::WinGenerator::operator()() const
    {
        static unsigned int n = 0;
        return windowMethod(n++, _N);
    }
}
