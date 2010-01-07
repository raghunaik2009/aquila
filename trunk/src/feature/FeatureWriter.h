/**
 * @file FeatureWriter.h
 *
 * Feature writer interface - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#ifndef FEATUREWRITER_H
#define FEATUREWRITER_H

#include "../global.h"
#include "Extractor.h"
#include <string>

namespace Aquila
{
    /**
     * Abstract base class of feature writer interface.
     */
    class AQUILA_EXPORT FeatureWriter
    {
    public:
        FeatureWriter(const std::string& filename);
        virtual ~FeatureWriter();

        /**
         * Writes the header and data - to be reimplemented in derived classes.
         *
         * @param hdr const reference to feature header
         * @param featureArray const reference to feature data array
         */
        virtual bool write(const FeatureHeader& hdr,
                           const Extractor::featureArrayType& featureArray) = 0;

    protected:
        /**
         * Output filename.
         */
        std::string m_filename;
    };
}

#endif // FEATUREWRITER_H
