/**
 * @file MelFilter.cpp
 *
 * Triangular filters in Mel frequency scale - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.3.3
 */

#include "MelFilter.h"

#include <cmath>

namespace Aquila
{
    /**
     * Creates the filter and sets sample frequency.
     *
     * @param sampleFrequency sample frequency in Hz
     */
    MelFilter::MelFilter(double sampleFrequency):
        sampFreq(sampleFrequency), enabled(true)
    {
    }

    /**
     * Designs the Mel filter and creates triangular spectrum.
     *
     * @param filterNum which filter in a sequence it is?
     * @param melFilterWidth filter width in Mel scale (eg. 200)
     * @param N filter spectrum size (must be the same as filtered spectrum)
     */
    void MelFilter::createFilter(unsigned short filterNum,
                                 unsigned short melFilterWidth, unsigned int N)
    {
        // calculating frequencies in Mel scale
        double melMinFreq = filterNum * melFilterWidth / 2.0;
        double melCenterFreq = melMinFreq + melFilterWidth / 2.0;
        double melMaxFreq = melMinFreq + melFilterWidth;

        // converting them to linear
        double minFreq = melToLinear(melMinFreq);
        double centerFreq = melToLinear(melCenterFreq);
        double maxFreq = melToLinear(melMaxFreq);

        // generating spectrum in linear scale
        generateFilterSpectrum(minFreq, centerFreq, maxFreq, N);
    }

    /**
     * Returns a single value computed by multiplying signal spectrum with
     * Mel filter spectrum, and summing all the products.
     *
     * @param dataSpectrum complex signal spectrum
     * @param N spectrum length
     * @return dot product of the spectra
     */
    double MelFilter::apply(const spectrumType& dataSpectrum,
                            unsigned int N) const
    {
        double value = 0.0;
        for (unsigned int i = 0; i < N / 2 - 1; ++i)
            value += std::abs(dataSpectrum[i]) * filterSpectrum[i];
        return value;
    }

    /**
     * Returns a single value computed by multiplying signal spectrum with
     * Mel filter spectrum, and summing all the products.
     *
     * This is an overload for real-valued data spectrum.
     *
     * @param dataAbsSpectrum magnitude of signal spectrum
     * @param N spectrum length
     * @return dot product of the spectra
     */
    double MelFilter::apply(const std::vector<double>& dataAbsSpectrum,
                            unsigned int N) const
    {
        double value = 0.0;
        for (unsigned int i = 0; i < N / 2 - 1; ++i)
            value += dataAbsSpectrum[i] * filterSpectrum[i];
        return value;
    }

    /**
     * Fills the vector with spectrum values, but in linear scale.
     *
     * @param minFreq low filter frequency in linear scale
     * @param centerFreq center filter frequency in linear scale
     * @param maxFreq high filter frequency in linear scale
     * @param N spectrum size
     */
    void MelFilter::generateFilterSpectrum(double minFreq, double centerFreq,
                                           double maxFreq, unsigned int N)
    {
        filterSpectrum.clear();
        filterSpectrum.resize(N);

        // scale the frequencies according to spectrum size
        minFreq *= N / sampFreq;
        centerFreq *= N / sampFreq;
        maxFreq *= N / sampFreq;


        // maximum and current value of the filter spectrum
        double max = 1.0, value;

        for (unsigned int k = 0; k < N; ++k)
        {
            // outside the triangle spectrum has 0 values
            if (k < minFreq || k > maxFreq)
            {
                value = 0.0;
            }
            else
            {
                // in the triangle, on the ascending slope
                if (k < centerFreq)
                {
                    value = k * max / (centerFreq - minFreq) -
                        minFreq * max / (centerFreq - minFreq);
                }
                // in the triangle, on the descending slope
                else
                {
                    value = k * max / (centerFreq - maxFreq) -
                        maxFreq * max / (centerFreq - maxFreq);
                }
            }

            filterSpectrum[k] = value;
        }
    }
}
