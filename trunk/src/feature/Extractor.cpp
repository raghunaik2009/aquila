/**
 * @file Extractor.cpp
 *
 * Feature extraction interface - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.4.6
 */

#include "Extractor.h"

#include "FeatureReader.h"
#include "FeatureWriter.h"
#include "../Exceptions.h"
#include <fstream>

namespace Aquila
{
    /**
     * Sets frame length and number of parameters per frame.
     *
     * @param frameLength frame length in milliseconds
     * @param paramsPerFrame number of params per frame
     */
    Extractor::Extractor(unsigned int frameLength, unsigned int paramsPerFrame):
        m_frameLength(frameLength), m_paramsPerFrame(paramsPerFrame), type(""),
        m_indicator(0)
    {
    }

    /**
     * Deletes feature object.
     */
    Extractor::~Extractor()
    {
    }

    /**
     * Saves calculated feature to a writer object (usually to file).
     *
     * @param writer non-const reference to a writer object
     */
    bool Extractor::save(FeatureWriter& writer)
    {
        FeatureHeader hdr;
        hdr.type = type;
        hdr.frameLength = m_frameLength;
        hdr.paramsPerFrame = m_paramsPerFrame;
        hdr.wavFilename = wavFilename;
        hdr.timestamp = std::time(0);

        return writer.write(hdr, featureArray);
    }

    /**
     * Reads feature from a reader object.
     *
     * @param reader non-const reference to a reader object
     */
    bool Extractor::read(FeatureReader& reader)
    {
        FeatureHeader hdr;
        featureArray.clear();
        if (reader.read(hdr, featureArray))
        {
            type = hdr.type;
            m_frameLength = hdr.frameLength;
            m_paramsPerFrame = hdr.paramsPerFrame;
            wavFilename = hdr.wavFilename;
            timestamp = hdr.timestamp;

            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Checks whether the two extractor objects are compatible with each other.
     *
     * @param other another Extractor object
     * @return true, if two extractors are compatible
     */
    bool Extractor::isCompatible(Extractor* other) const
    {
        return getType() == other->getType() &&
               getParamsPerFrame() == other->getParamsPerFrame() &&
               getFrameLength() == other->getFrameLength();
    }
}
