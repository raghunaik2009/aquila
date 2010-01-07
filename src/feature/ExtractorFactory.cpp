/**
 * @file ExtractorFactory.cpp
 *
 * A factory producing different extractor objects - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#include "ExtractorFactory.h"

#include "EnergyExtractor.h"
#include "MfccExtractor.h"
#include "PowerExtractor.h"
#include "../Exceptions.h"

namespace Aquila
{
    /**
     * Returns an extractor object according to parameters.
     *
     * Supported types: MFCC, Energy, Power.
     *
     * Feature objects are created on heap and must by deleted by caller!
     *
     * @param featureType feature type
     * @param frameLength frame length in milliseconds
     * @param paramsPerFrame number of features computed for each frame
     * @throw Aquila::Exception for an undefined feature type
     * @return pointer to object of one of Extractor-derived classes
     */
    Extractor* ExtractorFactory::getExtractor(const std::string& featureType,
                                              unsigned int frameLength,
                                              unsigned int paramsPerFrame)
    {
        if ("MFCC" == featureType)
        {
            return new MfccExtractor(frameLength, paramsPerFrame);
        }
        else if ("Energy" == featureType)
        {
            return new EnergyExtractor(frameLength);
        }
        else if ("Power" == featureType)
        {
            return new PowerExtractor(frameLength);
        }
        else
        {
            throw Exception("Unknown feature type: " + featureType);
        }
    }

    /**
     * Creates an extractor object according to header information.
     *
     * This method is a wrapper for the main getExtractor method.
     *
     * @param hdr feature header
     * @return pointer to object of one of Extractor-derived classes
     */
    Extractor* ExtractorFactory::getExtractor(const FeatureHeader& hdr)
    {
        return getExtractor(hdr.type, hdr.frameLength, hdr.paramsPerFrame);
    }
}


