/**
 * @file EnergyExtractor.h
 *
 * Energy extraction - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#ifndef ENERGYEXTRACTOR_H
#define ENERGYEXTRACTOR_H

#include "../global.h"
#include "Extractor.h"


namespace Aquila
{
    /**
     * Energy extraction class.
     */
    class AQUILA_EXPORT EnergyExtractor : public Extractor
    {
    public:
        EnergyExtractor(unsigned int frameLength);
        ~EnergyExtractor();

        void process(WaveFile* wav, const TransformOptions& options);
    };
}

#endif // ENERGYEXTRACTOR_H
