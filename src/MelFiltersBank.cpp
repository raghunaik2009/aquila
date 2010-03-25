/**
 * @file MelFiltersBank.cpp
 *
 * Mel filters bank - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.3
 * @since 0.3.3
 */

#include "MelFiltersBank.h"

namespace Aquila
{
    /**
     * Creates all the filters in the bank.
     *
     * @param sampleFrequency sample frequency in Hz
     * @param melFilterWidth filter width in Mel frequency scale
     * @param N spectrum size of each filter
     */
    MelFiltersBank::MelFiltersBank(double sampleFrequency,
                                   unsigned short melFilterWidth,
                                   unsigned int N):
        sampleFreq(sampleFrequency), N_(N)
    {
        filters.reserve(MELFILTERS);
        for (unsigned int i = 0; i < MELFILTERS; ++i)
        {
            filters.push_back(new MelFilter(sampleFrequency));
            filters[i]->createFilter(i, melFilterWidth, N);
        }
    }

    /**
     * Creates all the filters in the bank - tweaked for HFCC calculation.
     *
     * @param sampleFrequency sample frequency in Hz
     * @param N spectrum size of each filter
     * @param isHfcc a placeholder to overload the constructor
     */
    MelFiltersBank::MelFiltersBank(double sampleFrequency, unsigned int N,
                                   bool isHfcc):
        sampleFreq(sampleFrequency), N_(N)
    {
        // and here the magic happens ;)
        double f_low_global = 0.0, f_high_global = sampleFrequency / 2.0;
        const double a = 6.23e-6, b = 93.39e-3, c = 28.52;
        double a1 = 0.0, b1 = 0.0, c1 = 0.0, b2 = 0.0, c2 = 0.0;
        a1 = 0.5 / (700.0 + f_low_global);
        b1 = 700 / (700.0 + f_low_global);
        c1 = (-f_low_global / 2.0) * (1.0 + 700 / (700.0 + f_low_global));
        b2 = (b - b1)/(a - a1);
        c2 = (c - c1)/(a - a1);
        double fc_0 = 0.5 * (-b2 + sqrt(b2*b2 - 4*c2));
        a1 = -0.5 / (700.0 + f_high_global);
        b1 = -700 / (700.0 + f_high_global);
        c1 = (f_high_global / 2.0) * (1.0 + 700 / (700.0 + f_high_global));
        b2 = (b - b1)/(a - a1);
        c2 = (c - c1)/(a - a1);
        double fc_last = 0.5 * (-b2 + sqrt(b2*b2 - 4*c2));
        double fc_0_mel = MelFilter::linearToMel(fc_0);
        double fc_last_mel = MelFilter::linearToMel(fc_last);
        double delta_f_mel = (fc_last_mel - fc_0_mel) / double(MELFILTERS - 1);
        double fc_mel = 0.0, fc = 0.0, ERB = 0.0, f_low = 0.0, f_high;

        filters.reserve(MELFILTERS);
        for (unsigned int i = 0; i < MELFILTERS; i++)
        {
            if (0 == i)
            {
                fc_mel = fc_0_mel;
            }
            else if ((MELFILTERS - 1) == i)
            {
                fc_mel = fc_last_mel;
            }
            else
            {
                fc_mel = fc_0_mel + i * delta_f_mel;
            }
            // convert to linear scale, calculate ERB and filter boundaries
            fc = MelFilter::melToLinear(fc_mel);
            ERB = a * fc * fc + b * fc + c;
            f_low = -(700.0 + ERB) + sqrt((700.0 + ERB)*(700.0 + ERB) + fc*(fc + 1400));
            f_high = f_low + 2 * ERB;

            filters.push_back(new MelFilter(sampleFrequency));
            filters[i]->generateFilterSpectrum(f_low, fc, f_high, N);
        }
    }

    /**
     * Deletes filter objects.
     */
    MelFiltersBank::~MelFiltersBank()
    {
        for (unsigned int i = 0; i < MELFILTERS; ++i)
            delete filters[i];
    }

    /**
     * Processes frame spectrum through all filters.
     *
     * If a filter is enabled, the dot product of filter spectrum and frame
     * spectrum is computed. If the filter is disabled, 0 is inserted.
     *
     * The output vector must be initialized and its size must be MELFILTERS.
     *
     * @param frameSpectrum frame spectrum
     * @param N spectrum size
     * @param filtersOutput results vector
     */
    void MelFiltersBank::applyAll(spectrumType& frameSpectrum, unsigned int N,
                                  std::vector<double>& filtersOutput) const
    {
        // precalculate spectrum magnitude
        std::vector<double> frameAbsSpectrum;
        frameAbsSpectrum.reserve(N / 2 - 1);
        for (unsigned int i = 0; i < N/2 - 1; ++i)
        {
            frameAbsSpectrum.push_back(std::abs(frameSpectrum[i]));
        }

        for (unsigned int i = 0; i < MELFILTERS; ++i)
        {
            if (filters[i]->isEnabled())
                filtersOutput[i] = filters[i]->apply(frameAbsSpectrum, N);
            else
                filtersOutput[i] = 0.0;
        }
    }

    /**
     * Enables only selected filters.
     *
     * @param enabledFilters an array representing the selection
     */
    void MelFiltersBank::setEnabledFilters(bool enabledFilters[])
    {
        if (filters.empty())
            return;

        for (unsigned int i = 0; i < MELFILTERS; ++i)
            filters[i]->setEnabled(enabledFilters[i]);
    }
}

