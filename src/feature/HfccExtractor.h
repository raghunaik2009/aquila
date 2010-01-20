/**
 * @file HfccExtractor.h
 *
 * HFCC feature extraction - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.1
 * @since 2.5.1
 */

#ifndef HFCCEXTRACTOR_H
#define HFCCEXTRACTOR_H

#include "../global.h"
#include "MfccExtractor.h"

namespace Aquila
{
    /**
     * HFCC feature extractor, basing on MFCC.
     */
    class AQUILA_EXPORT HfccExtractor : public MfccExtractor
    {
    public:
        HfccExtractor(unsigned int frameLength, unsigned int paramsPerFrame);
        ~HfccExtractor();

    protected:
        void updateFilters(unsigned int frequency, unsigned int N);
    };
}

#endif // HFCCEXTRACTOR_H
