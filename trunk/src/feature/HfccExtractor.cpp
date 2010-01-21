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

#include "../MelFiltersBank.h"

namespace Aquila
{
    MelFiltersBank* HfccExtractor::hfccFilters = 0;

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
     * Calculates HFCC features for each frame.
     *
     * @param wav recording object
     * @param options transform options
     */
    void HfccExtractor::process(WaveFile* wav, const TransformOptions& options)
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
        std::vector<double> frameHfcc(m_paramsPerFrame);
        Transform transform(options);

        // for each frame: FFT -> Mel filtration -> DCT
        for (unsigned int i = 0; i < framesCount; ++i)
        {
            transform.fft(wav->frames[i], frameSpectrum);
            hfccFilters->applyAll(frameSpectrum, N, filtersOutput);
            transform.dct(filtersOutput, frameHfcc);
            featureArray[i] = frameHfcc;

            if (m_indicator)
                m_indicator->progress(i);
        }

        if (m_indicator)
            m_indicator->stop();
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
        if (!hfccFilters)
        {
            hfccFilters = new MelFiltersBank(frequency, N, true);
        }
        else
        {
            if (hfccFilters->getSampleFrequency() != frequency ||
                hfccFilters->getSpectrumLength() != N)
            {
                delete hfccFilters;
                hfccFilters = new MelFiltersBank(frequency, N, true);
            }
        }

        if (enabledFilters)
            hfccFilters->setEnabledFilters(enabledFilters);
    }
}
