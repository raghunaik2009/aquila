/**
 * @file Transform.h
 *
 * A few common signal transformations - header.
 *
 * The Transform class is a collection of methods used for
 * most important calculations like Fast Fourier Transform,
 * frame power, frame energy, Discrete Cosine Transform etc.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.2.0
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "global.h"
#include "Frame.h"
#include "Window.h"
#include <functional>
#include <map>
#include <utility>


namespace Aquila
{
	/**
     * ln(2) - needed for calculating number of stages in FFT.
	 */
	const double LN_2 = 0.69314718055994530941723212145818;

	/**
     * A functor class used for calculating energy or power of the signal.
	 */
    class SquareAndSum : public std::binary_function<double, double, double>
    {
    public:
        /**
         * Adds square of the second value to the first one.
         *
         * @param x initial value
         * @param y squared value
         * @return sum of initial value and squared value
         */
        double operator()(double x, double y) const
        {
            return x + y * y;
        }
    };

    /**
     * A simple wrapper for few of the transformation options.
     */
    struct AQUILA_EXPORT TransformOptions
    {
        unsigned int zeroPaddedLength;
        WindowType windowType;
        double preemphasisFactor;
    };

	/**
     * The transform class.
	 */
    class AQUILA_EXPORT Transform
	{
	public:
        /**
         * Complex unit (0.0 + 1.0j).
         */
        static const cplx j;

        /**
         * Creates the transform object and explicitly sets the options.
         *
         * @param length spectrum length (a power of 2)
         * @param window type of used window function (default is Hamming)
         * @param factor preemphasis factor (default is 0.95)
         */
        Transform(unsigned int length, WindowType window = WIN_HAMMING,
            double factor = 0.95):
            zeroPaddedLength(length), preemphasisFactor(factor), winType(window)
        {
        }

        /**
         * Creates the transform object and sets groupped options.
         *
         * @param options a struct of type TransformOptions
         */
        Transform(TransformOptions options):
            zeroPaddedLength(options.zeroPaddedLength),
            preemphasisFactor(options.preemphasisFactor),
            winType(options.windowType)
        {
        }

        /**
         * Makes sure no memory leaks are caused by the cache.
         */
        ~Transform()
        {
            clearCache();
        }

        double frameLogEnergy(const Frame* frame);
        double framePower(const Frame* frame) ;

        double fft(const std::vector<double>& data, spectrumType& spectrum);
        double fft(const Frame* frame, spectrumType& spectrum);

        void dct(const std::vector<double>& data,
                std::vector<double>& output);

    private:
        /**
         * Frame length after padding with zeros.
         */
        unsigned int zeroPaddedLength;

        /**
         * Preemphasis factor.
         */
        double preemphasisFactor;

        /**
         * Window function type.
         */
        WindowType winType;

        // COSINE CACHING FOR DCT
        /**
         * Key type for the cache, using input and output length.
         */
        typedef std::pair<unsigned int, unsigned int> cosineCacheKeyType;

        /**
         * Cache type.
         */
        typedef std::map<cosineCacheKeyType, double**> cosineCacheType;

        /**
         * Cache object, implemented as a map.
         */
        cosineCacheType cosineCache;

        double** getCachedCosines(unsigned int inputLength, unsigned int outputLength);

        void clearCache();
	};
}

#endif
