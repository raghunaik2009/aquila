/**
 * @file HfccExtractor.cpp
 *
 * HFCC feature extraction - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.1
 * @since 2.5.1
 */

#include "HfccExtractor.h"

namespace Aquila
{
    /**
     * Sets frame length and number of parameters per frame.
     *
     * @param frameLength frame length in milliseconds
     * @param paramsPerFrame number of params per frame
     */
    HfccExtractor::HfccExtractor(unsigned int frameLength,
                                 unsigned int paramsPerFrame):
        MfccExtractor(frameLength, paramsPerFrame)
    {
        type = "HFCC";
    }

    /**
     * Deletes the extractor object.
     */
    HfccExtractor::~HfccExtractor()
    {
    }

    /**
     * Updates the filter bank.
     *
     * (Re)creates new filter bank when sample frequency or spectrum size
     * changed. If requested, enables only some filters.
     *
     * @param frequency sample frequency
     * @param N spectrum size
     */
    void HfccExtractor::updateFilters(unsigned int frequency, unsigned int N)
    {
        if (!filters)
        {
            filters = new MelFiltersBank(frequency, N, true);
        }
        else
        {
            if (filters->getSampleFrequency() != frequency ||
                filters->getSpectrumLength() != N)
            {
                delete filters;
                filters = new MelFiltersBank(frequency, N, true);
            }
        }

        if (enabledFilters)
            filters->setEnabledFilters(enabledFilters);
    }
}
