/**
 * @file Extractor.h
 *
 * Feature extraction interface - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.4.6
 */

#ifndef EXTRACTOR_H_
#define EXTRACTOR_H_

#include "../global.h"
#include "../WaveFile.h"
#include "../Transform.h"
#include "../ProcessingIndicator.h"
#include <ctime>
#include <string>
#include <vector>


namespace Aquila
{
    /**
     * Forward reference to writer class.
     */
    class FeatureWriter;

    /**
     * Forward reference to reader class.
     */
    class FeatureReader;

    /**
     * Simple structure to provde header data for readers/writers.
     */
    struct AQUILA_EXPORT FeatureHeader
    {
        std::string type;
        unsigned int frameLength;
        unsigned int paramsPerFrame;
        std::string wavFilename;
        std::time_t timestamp;
    };

    /**
     * Abstract base class - an interface to feature extraction.
     */
    class AQUILA_EXPORT Extractor
    {
    public:
        /**
         * Type of the feature array, in our case vector of vectors of doubles.
         */
        typedef std::vector< std::vector<double> > featureArrayType;

        Extractor(unsigned int frameLength, unsigned int paramsPerFrame);
        virtual ~Extractor();

        /**
         * To be reimplemented in derived classes.
         *
         * @param wav instance of wave file object
         * @param options various transformation options
         */
        virtual void process(WaveFile* wav,
                             const TransformOptions& options) = 0;

        bool save(FeatureWriter& writer);

        bool read(FeatureReader& reader);

        /**
         * Returns frame length of the data.
         *
         * @return frame length in milliseconds
         */
        unsigned int getFrameLength() const { return m_frameLength; }

        /**
         * Returns number of calculated parameters per frame.
         *
         * @return how many feature parameters are computed for each frame
         */
        unsigned int getParamsPerFrame() const { return m_paramsPerFrame; }

        /**
         * Returns the type, or name, of the extractor.
         *
         * @return feature type
         */
        std::string getType() const { return type; }

        /**
         * Returns how many frames are processed.
         *
         * @return first dimension of the feature array
         */
        unsigned int getFramesCount() const { return featureArray.size(); }

        /**
         * Returns the name of source wave file.
         *
         * @return full path to the file
         */
        std::string getWaveFilename() const { return wavFilename; }

        /**
         * Returns timestamp of feature save.
         *
         * @param timestamp at the moment of saving feature file
         */
        std::time_t getTimestamp() const { return timestamp; }

        /**
         * Sets an optional processing indicator.
         *
         * @param indicator pointer to an indicator object
         */
        void setProcessingIndicator(ProcessingIndicator* indicator)
            { m_indicator = indicator; }

        /**
         * Returns feature value at given coordinates.
         *
         * @param x frame number
         * @param y param number
         * @return y-th param in x-th frame
         */
        double getParam(int x, int y) const { return featureArray[x][y]; }

        bool isCompatible(Extractor* other) const;

        /**
         * Enables access to single feature vector of a given frame.
         *
         * @param frame frame number
         * @return const reference to feature vector
         */
        const std::vector<double>& getVector(unsigned int frame) const
            { return featureArray[frame]; }

    protected:
        /**
         * Frame length.
         */
        unsigned int m_frameLength;

        /**
         * Number of params (features) calculated for each frame.
         */
        unsigned int m_paramsPerFrame;

        /**
         * Computed feature array.
         */
        featureArrayType featureArray;

        /**
         * Feature type.
         */
        std::string type;

        /**
         * Filename of the recording being processed.
         */
        std::string wavFilename;

        /**
         * Time when feature data was saved to file.
         */
        std::time_t timestamp;

        /**
         * Optional processing indicator.
         */
        ProcessingIndicator* m_indicator;
    };
}

#endif /* EXTRACTOR_H_ */
