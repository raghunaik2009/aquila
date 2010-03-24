/**
 * @file FeatureReader.h
 *
 * Feature reader interface - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#ifndef FEATUREREADER_H
#define FEATUREREADER_H

#include "../global.h"
#include "Extractor.h"
#include <string>

namespace Aquila
{
    /**
     * Abstract base class of feature reader interface.
     */
    class AQUILA_EXPORT FeatureReader
    {
    public:
        FeatureReader(const std::string& filename);
        virtual ~FeatureReader();

        /**
         * Reads only the header - to be reimplemented in derived classes.
         *
         * @param hdr non-const reference to feature header
         */
        virtual bool readHeader(FeatureHeader& hdr) = 0;

        /**
         * Reads the header and data - to be reimplemented in derived classes.
         *
         * @param hdr non-const reference to feature header
         * @param featureArray non-const reference to feature data array
         */
        virtual bool read(FeatureHeader& hdr,
                          Extractor::featureArrayType& featureArray) = 0;

    protected:
        /**
         * Input filename.
         */
        std::string m_filename;
    };
}

#endif // FEATUREREADER_H
