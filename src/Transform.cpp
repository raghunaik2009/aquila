/**
 * @file Transform.cpp
 *
 * A few common signal transformations - implementation.
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

#include "Transform.h"

#include "Window.h"
#include <cmath>
#include <numeric>

namespace Aquila
{
	const cplx Transform::j(0, 1);

    /**
     * Calculates logarithm of a frame energy.
     *
     * Energy is a sum of squares of all samples in the frame.
     *
     * @param frame pointer to Frame object
     * @return frame log energy (when greater than 0)
     */
	double Transform::frameLogEnergy(const Frame* frame)
	{
        double energy = std::accumulate(frame->begin(), frame->end(),
                0.0, SquareAndSum());

        return (energy > 0) ? std::log10(energy) : 0.0;
	}

    /**
     * Calculates frame power.
     *
     * Frame power is the energy normalized by frame length.
     *
     * @param frame pointer to Frame object
     * @return frame power
     */
    double Transform::framePower(const Frame* frame)
    {
        double energy = std::accumulate(frame->begin(), frame->end(),
                0.0, SquareAndSum());

        return energy / frame->getLength();
    }

    /**
     * Calculates Fast Fourier Transform using radix-2 algorithm.
     *
     * Input data is given as a const reference to the data vector.
     * Output spectrum is written to the spectrum vector, which must be
     * initialized prior to the call to fft(). The spectrum is
     * normalized by N/2, wher N is input data length. The method
     * returns maximum magnitude of the calculated spectrum, which
     * can be used for example to scale a frequency plot.
     *
     * @param data const reference to input data vector
     * @param spectrum initialized complex vector of the same length as data
     * @return maximum magnitude of the spectrum
     */
	double Transform::fft(const std::vector<double>& data,
	        spectrumType& spectrum)
	{
        // input signal size
		unsigned int N = data.size();

        // bit-reversing the samples - a requirement of radix-2
        // instead of reversing in place, put the samples to result vector
		unsigned int a = 1, b = 0, c = 0;
		for (b = 1; b < N; ++b)
		{
			if (b < a)
			{
				spectrum[a - 1] = data[b - 1];
				spectrum[b - 1] = data[a - 1];
			}
			c = N / 2;
			while (c < a)
			{
				a -= c;
				c /= 2;
			}
			a += c;
		}

        // FFT calculation using "butterflies"
        // code ported from Matlab, based on book by Tomasz P. Zieliński

        // FFT stages count
		unsigned int numStages = static_cast<unsigned int>(
		        std::log(double(N)) / LN_2);

        // L = 2^k - DFT block length and offset
        // M = 2^(k-1) - butterflies per block, butterfly width
        // p - butterfly index
        // q - block index
        // r - index of sample in butterfly
        // Wi - starting value of Fourier base coefficient
        // W - Fourier base multiplying factor
		unsigned int L = 0, M = 0, p = 0, q = 0, r = 0;
        cplx Wi(0, 0), Temp(0, 0);

        cplx** Wi_cache = getCachedFftWi(numStages);

        // iterate over the stages
		for (unsigned int k = 1; k <= numStages; ++k)
		{
            L = 1 << k;
            M = 1 << (k - 1);
            Wi = Wi_cache[k][0];

            // iterate over butterflies
			for (p = 1; p <= M; ++p)
			{
                // iterate over blocks
				for (q = p; q <= N; q += L)
				{
                    r = q + M;
                    Temp = spectrum[r - 1] * Wi;
                    spectrum[r - 1] = spectrum[q - 1] - Temp;
                    spectrum[q - 1] = spectrum[q - 1] + Temp;
				}
                Wi = Wi_cache[k][p];
			}
		}

		double maxAbs = 0.0, currAbs = 0.0;
		unsigned int N2 = N >> 1; // N/2

        // scaling by N/2 and searching for maximum magnitude
        // we can iterate only over the first half of the spectrum,
        // because of the symmetry, yet scaling is applied
        // to both halves
		for (unsigned int k = 0; k < N2; ++k)
		{
			spectrum[k] /= N2;
			spectrum[N2 + k] /= N2;
			currAbs = std::abs(spectrum[k]);
			if ((currAbs > maxAbs))
				maxAbs = currAbs;
		}

		return maxAbs;
	}

    /**
     * Calculates FFT of a signal frame using radix-2 algorithm.
     *
     * Input data is given as a pointer to Frame object.
     * Output spectrum is written to the spectrum vector, which must be
     * initialized prior to the call to fft(). The spectrum is
     * normalized by N/2, wher N is input frame length (zero-padded).
     * The method  returns maximum magnitude of the calculated spectrum,
     * which can be used for example to scale a frequency plot.
     *
     * @param frame pointer to Frame object
     * @param spectrum initialized complex vector of the same length as data
     * @return maximum magnitude of the spectrum
     * @since 2.0.1
     */
	double Transform::fft(const Frame* frame, spectrumType& spectrum)
	{
        // the vector is initialized to zero padded length,
        // what means that it contains default values of contained type
        // (0.0 in case of double); that allows us to loop
        // only to frame length without padding and
        // automatically have zeros at the end of data
        std::vector<double> data(zeroPaddedLength);
        unsigned int length = frame->getLength();
        Frame::iterator it = frame->begin(), end = frame->end();

        // first sample does not need preemphasis
        data[0] = *it;
        ++it;
        double current = 0.0, previous = data[0];

        // iterate over all samples of the frame
        // filter the data through preemphasis
        // and apply a chosen window function
        for (unsigned int n = 1; it != end; ++it, ++n)
        {
            current = *it;
            data[n] = (current - preemphasisFactor * previous) *
                    Window::apply(winType, n, length);
            previous = current;
        }

        return fft(data, spectrum);
	}

    /**
     * Calculates the Discrete Cosine Transform.
     *
     * Uses cosine value caching in order to speed up computations.
     *
     * @param data input data vector
     * @param output initialized vector of output values
     */
	void Transform::dct(const std::vector<double>& data,
	        std::vector<double>& output)
	{
	    using namespace std;

        // output size determines how many coefficients will be calculated
		unsigned int outputLength = output.size();
		unsigned int inputLength = data.size();

        // DCT scaling factor
        double c0 = sqrt(1.0 / inputLength);
        double cn = sqrt(2.0 / inputLength);
        // cached cosine values
        double** cosines = getCachedCosines(inputLength, outputLength);

		for (unsigned int n = 0; n < outputLength; ++n)
		{
			output[n] = 0.0;
			for (unsigned int k = 0; k < inputLength; ++k)
			{
                // 1e-10 added for the logarithm value to be grater than 0
                output[n] += log(fabs(data[k]) + 1e-10) * cosines[n][k];
			}

            output[n] *= (0 == n) ? c0 : cn;
		}
	}

    /**
     * Returns a table of DCT cosine values stored in memory cache.
     *
     * The two params unambigiously identify which cache to use.
     *
     * @param inputLength length of the input vector
     * @param outputLength length of the output vector
     * @return pointer to array of pointers to arrays of doubles
     */
    double** Transform::getCachedCosines(unsigned int inputLength, unsigned int outputLength)
    {
        cosineCacheKeyType key = std::make_pair(inputLength, outputLength);

        // if we have that key cached, return immediately!
        if (cosineCache.find(key) != cosineCache.end())
        {
            return cosineCache[key];
        }

        // nothing in cache for that pair, calculate cosines
        double** cosines = new double*[outputLength];
        for (unsigned int n = 0; n < outputLength; ++n)
        {
            cosines[n] = new double[inputLength];

            for (unsigned int k = 0; k < inputLength; ++k)
            {
                // from the definition of DCT
                cosines[n][k] = cos((M_PI * (2*k+1) * n) /
                                    (2 * inputLength));
            }
        }

        // store in cache and return
        cosineCache[key] = cosines;

        return cosines;
    }

    /**
     * Deletes all the memory used by cache.
     */
    void Transform::clearCosineCache()
    {
        cosineCacheType::const_iterator it;
        for (it = cosineCache.begin(); it != cosineCache.end(); it++)
        {
            cosineCacheKeyType key = it->first;
            double** cosines = it->second;
            unsigned int outputLength = key.second;
            for (unsigned int i = 0; i < outputLength; ++i)
            {
                delete [] cosines[i];
            }
            delete [] cosines;
        }
    }


    /**
     * Returns a table of Wi (twiddle factors) stored in cache.
     *
     * @param numStages the FFT stages count
     * @return pointer to an array of pointers to arrays of complex numbers
     */
    cplx** Transform::getCachedFftWi(unsigned int numStages)
    {
        fftWiCacheKeyType key = numStages;
        // cache hit, return immediately
        if (fftWiCache.find(key) != fftWiCache.end())
        {
            return fftWiCache[key];
        }

        // nothing in cache, calculate twiddle factors
        cplx** Wi = new cplx*[numStages+1];
        for (unsigned int k = 1; k <= numStages; ++k)
        {
            unsigned int L = 1 << k;
            unsigned int M = 1 << (k-1);
            cplx W = exp((-j) * 2.0 * M_PI / double(L));
            Wi[k] = new cplx[M+1];
            Wi[k][0] = cplx(1.0);
            for (unsigned int p = 1; p <= M; ++p)
            {
                Wi[k][p] = Wi[k][p-1] * W;
            }
        }

        // store in cache and return
        fftWiCache[key] = Wi;

        return Wi;
    }

    /**
     * Clears the twiddle factor cache.
     */
    void Transform::clearFftWiCache()
    {
        fftWiCacheType::const_iterator it;
        for (it = fftWiCache.begin(); it != fftWiCache.end(); it++)
        {
            cplx** c = it->second;
            unsigned int numStages = it->first;
            for (unsigned int i = 1; i <= numStages; ++i)
            {
                delete [] c[i];
            }

            delete [] c;
        }
    }
}
