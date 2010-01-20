/**
 * @file ExtractorFactory.h
 *
 * A factory producing different extractor objects - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.1
 * @since 2.3.0
 */

#ifndef EXTRACTORFACTORY_H
#define EXTRACTORFACTORY_H

#include "../global.h"
#include "Extractor.h"
#include <string>


namespace Aquila
{
    /**
     * A factory class producing different extractor objects.
     */
    class AQUILA_EXPORT ExtractorFactory
    {
    public:
        static Extractor* getExtractor(const std::string& featureType,
                                       unsigned int frameLength,
                                       unsigned int paramsPerFrame = 1);

        static Extractor* getExtractor(const FeatureHeader& hdr);
    };
}

#endif // EXTRACTORFACTORY_H
