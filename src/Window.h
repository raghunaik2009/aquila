/**
 * @file Window.h
 *
 * Window functions - header.
 *
 * A signal frame should be multiplied by a time window before processing,
 * to decrease the magnitude of side lobes.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.6.0
 * @since 0.5.4
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "global.h"
#include "Cache.h"
#include <boost/shared_array.hpp>
#include <cmath>
#include <map>
#include <utility>
#include <vector>

namespace Aquila
{
	/**
     * Possible window functions.
	 */
    enum WindowType {WIN_RECT, WIN_HAMMING, WIN_HANN, WIN_BARLETT, WIN_BLACKMAN,
                     WIN_FLATTOP };


	/**
     * Class defining different window types as static methods.
     *
     * Windows are cached with window type combined with its length
     * as a key. It is an efficient way to reduce calls to math functions.
	 */
    class AQUILA_EXPORT Window
	{
	public:
		static double apply(WindowType type, unsigned int n, unsigned int N);

	private:
        /**
         * Key type for the window cache.
         */
        typedef std::pair<WindowType, unsigned int> keyType;

        /**
         * Window cache type.
         */
        typedef Cache<keyType, boost::shared_array<double> > WindowCacheType;

        /**
         * Window cache.
         */
        static WindowCacheType windowsCache;

        static boost::shared_array<double> createWindow(const keyType& windowKey);

        static double rectangular(unsigned int n, unsigned int N);
        static double hamming(unsigned int n, unsigned int N);
        static double hann(unsigned int n, unsigned int N);
        static double barlett(unsigned int n, unsigned int N);
        static double blackman(unsigned int n, unsigned int N);
        static double flattop(unsigned int n, unsigned int N);

        /**
         * Private functor class for window generation.
         */
        class WinGenerator
        {
        public:
            WinGenerator(WindowType type, unsigned int N);
            double operator()() const;

        private:
            /**
             * Window size.
             */
            unsigned int _N;

            /**
             * Pointer to window function.
             */
            double (*windowMethod)(unsigned int, unsigned int);
        };
	};
}

#endif
