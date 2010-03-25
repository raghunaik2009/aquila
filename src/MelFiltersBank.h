/**
 * @file MelFiltersBank.h
 *
 * Mel filters bank - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.3
 * @since 0.3.3
 */

#ifndef MELFILTERSBANK_H
#define MELFILTERSBANK_H

#include "global.h"
#include "MelFilter.h"
#include <vector>

namespace Aquila
{
    /**
     * A wrapper class for a vector of triangular filters.
     */
    class AQUILA_EXPORT MelFiltersBank
    {
    public:
        MelFiltersBank(double sampleFrequency, unsigned short melFilterWidth,
                       unsigned int N);
        MelFiltersBank(double sampleFrequency, unsigned int N,
                       bool isHfcc = true);
        ~MelFiltersBank();

        void applyAll(spectrumType& frameSpectrum, unsigned int N,
                      std::vector<double>& filtersOutput) const;

        void setEnabledFilters(bool enabledFilters[]);

        /**
         * Returns sample frequency of all filters.
         *
         * @return sample frequency in Hz
         */
        double getSampleFrequency() const { return sampleFreq; }

        /**
         * Returns spectrum size of any filter spectra.
         *
         * @return spectrum size
         */
        unsigned int getSpectrumLength() const { return N_; }

    private:
        /**
         * Vector of pointers to Mel filters (allocated on heap).
         */
        std::vector<MelFilter*> filters;

        /**
         * Sample frequency of the filtered signal.
         */
        double sampleFreq;

        /**
         * Filter spectrum size (equal to zero-padded length of signal frame).
         */
        unsigned int N_;
    };
}

#endif // MELFILTERSBANK_H
