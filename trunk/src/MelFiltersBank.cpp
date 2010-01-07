/**
 * @file MelFiltersBank.cpp
 *
 * Mel filters bank - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
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
        for (unsigned int i = 0; i < MELFILTERS; ++i)
        {
            if (filters[i]->isEnabled())
                filtersOutput[i] = filters[i]->apply(frameSpectrum, N);
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

