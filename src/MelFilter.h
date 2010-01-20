/**
 * @file MelFilter.h
 *
 * Triangular filters in Mel frequency scale - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.3.3
 */

#ifndef MELFILTER_H
#define MELFILTER_H

#include "global.h"
#include <cmath>
#include <vector>

namespace Aquila
{
    /**
     * Encapsulation of a single Mel-frequency filter.
     */
    class AQUILA_EXPORT MelFilter
    {
    public:
        friend class MelFiltersBank;

        explicit MelFilter(double sampleFrequency);

        void createFilter(unsigned short filterNum,
                          unsigned short melFilterWidth, unsigned int N);

        double apply(const spectrumType& dataSpectrum, unsigned int N) const;

        /**
         * Turns on/off the filter.
         *
         * param enable true - filter enabled; false - filter disabled
         */
        void setEnabled(bool enable) { enabled = enable; }

        /**
         * Checks if the filter is enabled.
         *
         * @return true, when the filter is enabled
         */
        bool isEnabled() const { return enabled; }

        /**
         * Converts frequency from linear to Mel scale.
         *
         * @param lFrequency frequency in linear scale
         * @return frequency in Mel scale
         */
        static double linearToMel(const double lFrequency)
        {
            return 1127.01048 * std::log(1 + lFrequency / 700.0);
        }

        /**
         * Converts frequency from Mel to linear scale.
         *
         * @param mFrequency frequency in Mel scale
         * @return frequency in linear scale
         */
        static double melToLinear(const double mFrequency)
        {
            return 700.0 * (std::exp(mFrequency / 1127.01048) - 1);
        }

    private:
        /**
         * Sample frequency of a signal which spectrum is to be filtered.
         */
        double sampFreq;

        /**
         * Filter spectrum (real).
         */
        std::vector<double> filterSpectrum;

        /**
         * Is the filter enabled.
         */
        bool enabled;

        void generateFilterSpectrum(double minFreq, double centerFreq,
                                    double maxFreq, unsigned int N);
    };
}

#endif // MELFILTER_H
