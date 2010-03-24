/**
 * @file PowerExtractor.h
 *
 * Power extraction - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#ifndef POWEREXTRACTOR_H
#define POWEREXTRACTOR_H

#include "../global.h"
#include "Extractor.h"

namespace Aquila
{
    /**
     * Power extraction class.
     */
    class AQUILA_EXPORT PowerExtractor : public Extractor
    {
    public:
        PowerExtractor(unsigned int frameLength);
        ~PowerExtractor();

        void process(WaveFile* wav, const TransformOptions& options);
    };
}

#endif // POWEREXTRACTOR_H
