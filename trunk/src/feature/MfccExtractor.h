/**
 * @file MfccExtractor.h
 *
 * MFCC feature extraction - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.1
 * @since 0.4.6
 */

#ifndef MFCCEXTRACTOR_H_
#define MFCCEXTRACTOR_H_

#include "../global.h"
#include "Extractor.h"
#include "../MelFiltersBank.h"

namespace Aquila
{
    /**
     * MFCC feature extractor.
     */
    class AQUILA_EXPORT MfccExtractor : public Extractor
    {
    public:
        MfccExtractor(unsigned int frameLength, unsigned int paramsPerFrame);
        ~MfccExtractor();

        void process(WaveFile* wav, const TransformOptions& options);

        void setEnabledMelFilters(bool enabled[]);

    protected:
        /**
         * Mel filters bank, static and common to all MFCC extractors.
         */
        static MelFiltersBank* filters;

        /**
         * Selection of enabled Mel filters.
         */
        bool* enabledFilters;

        virtual void updateFilters(unsigned int frequency, unsigned int N);
    };
}

#endif /* MFCCEXTRACTOR_H_ */
