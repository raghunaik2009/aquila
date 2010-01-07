/**
 * @file MfccExtractor.cpp
 *
 * MFCC feature extraction - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.4.6
 */

#include "MfccExtractor.h"

#include "../global.h"
#include "../Transform.h"
#include <algorithm>

namespace Aquila
{
    MelFiltersBank* MfccExtractor::filters = 0;

    /**
     * Sets frame length and number of parameters per frame.
     *
     * @param frameLength frame length in milliseconds
     * @param paramsPerFrame number of params per frame
     */
    MfccExtractor::MfccExtractor(unsigned int frameLength,
                                 unsigned int paramsPerFrame):
        Extractor(frameLength, paramsPerFrame), enabledFilters(0)
    {
        type = "MFCC";
    }

    /**
     * Deletes the extractor object.
     */
    MfccExtractor::~MfccExtractor()
    {
        delete [] enabledFilters;
    }

    /**
     * Calculates MFCC features for each frame.
     *
     * @param wav recording object
     * @param options transform options
     */
    void MfccExtractor::process(WaveFile* wav, const TransformOptions& options)
    {
        wavFilename = wav->getFilename();

        unsigned int framesCount = wav->getFramesCount();
        featureArray.resize(framesCount);

        if (m_indicator)
            m_indicator->start(0, framesCount-1);

        unsigned int N = wav->getSamplesPerFrameZP();
        updateFilters(wav->getSampleFrequency(), N);

        spectrumType frameSpectrum(N);
        std::vector<double> filtersOutput(MELFILTERS);
        std::vector<double> frameMfcc(m_paramsPerFrame);
        Transform transform(options);

        // for each frame: FFT -> Mel filtration -> DCT
        for (unsigned int i = 0; i < framesCount; ++i)
        {
            transform.fft(wav->frames[i], frameSpectrum);
            filters->applyAll(frameSpectrum, N, filtersOutput);
            transform.dct(filtersOutput, frameMfcc);
            featureArray[i] = frameMfcc;

            if (m_indicator)
                m_indicator->progress(i);
        }

        if (m_indicator)
            m_indicator->stop();
    }
    
    /**
     * Enables only selected Mel filters.
     */
    void MfccExtractor::setEnabledMelFilters(bool enabled[])
    {
        delete [] enabledFilters;
        enabledFilters = new bool[MELFILTERS];

        for (unsigned int i = 0; i < MELFILTERS; ++i)
        {
            enabledFilters[i] = enabled[i];
        }
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
    void MfccExtractor::updateFilters(unsigned int frequency, unsigned int N)
    {
        if (!filters)
        {
            filters = new MelFiltersBank(frequency, 200, N);
        }
        else
        {
            if (filters->getSampleFrequency() != frequency ||
                filters->getSpectrumLength() != N)
            {
                delete filters;
                filters = new MelFiltersBank(frequency, 200, N);
            }
        }

        if (enabledFilters)
            filters->setEnabledFilters(enabledFilters);
    }
}
