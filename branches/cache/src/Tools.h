/**
 * @file Tools.h
 *
 * Some utility methods - header.
 *
 * @author Zbigniew Siciarz
 * @date 2009-2010
 * @version 2.5.0
 * @since 2.2.1
 */

#ifndef TOOLS_H
#define TOOLS_H

#include "global.h"
#include "Window.h"
#include <string>


namespace Aquila
{
    /**
     * Static utility class grouping some functions.
     */
    class AQUILA_EXPORT Tools
    {
    public:
        /**
         * Converts number of a spectral peak to frequency in Hz.
         *
         * @param peakNum peak number
         * @param sampleFrequency sample frequency
         * @param spectrumSize spectrum size
         * @return frequency in Hz
         */
        static double spectrumPeakToHz(double peakNum, double sampleFrequency,
                                       unsigned int spectrumSize)
        {
            return sampleFrequency * peakNum / spectrumSize;
        }

        /**
         * Converts frame number to time in milliseconds.
         *
         * @param frameNum frame number
         * @param frameLength frame length in milliseconds
         * @param frameOverlap frame overlap
         * @return time from the beginning of the recording in milliseconds
         */
        static double frameNumToMs(double frameNum, int frameLength,
                                   double frameOverlap)
        {
            return (1.0 - frameOverlap) * frameLength * frameNum;
        }

        static std::string windowTypeToString(WindowType type);

        static WindowType stringToWindowType(const std::string& name);
    };
}

#endif // TOOLS_H
