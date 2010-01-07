/**
 * @file PowerExtractor.cpp
 *
 * Power extraction - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#include "PowerExtractor.h"

#include "../Transform.h"
#include <vector>

namespace Aquila
{
    /**
     * Constructor needs only the frame length, paramsPerFrame = 1.
     *
     * @param frameLength frame length in milliseconds
     */
    PowerExtractor::PowerExtractor(unsigned int frameLength):
        Extractor(frameLength, 1)
    {
        type = "Power";
    }

    /**
     * Deletes the feature object.
     */
    PowerExtractor::~PowerExtractor()
    {
    }

    /**
     * Calculates power for each frame.
     *
     * @param wav recording object
     * @param options transform options
     */
    void PowerExtractor::process(WaveFile* wav, const TransformOptions& options)
    {
        wavFilename = wav->getFilename();

        unsigned int framesCount = wav->getFramesCount();
        featureArray.resize(framesCount);

        if (m_indicator)
            m_indicator->start(0, framesCount-1);

        Transform transform(options);
        for (unsigned int i = 0; i < framesCount; ++i)
        {
            std::vector<double> params;
            params.push_back(transform.framePower(wav->frames[i]));
            featureArray[i] = params;

            if (m_indicator)
                m_indicator->progress(i);
        }

        if (m_indicator)
            m_indicator->stop();
    }
}
