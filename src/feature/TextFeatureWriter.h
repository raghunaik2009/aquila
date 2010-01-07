/**
 * @file TextFeatureWriter.h
 *
 * A simple text writer - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#ifndef TEXTFEATUREWRITER_H
#define TEXTFEATUREWRITER_H

#include "../global.h"
#include "FeatureWriter.h"


namespace Aquila
{
    /**
     * A plain-text feature writer.
     */
    class AQUILA_EXPORT TextFeatureWriter: public FeatureWriter
    {
    public:
        /**
         * Creates the writer object and assigns filename.
         *
         * @param filename full path to output file
         */
        TextFeatureWriter(const std::string& filename):
            FeatureWriter(filename)
        {
        }

        /**
         * Deletes the writer.
         */
        virtual ~TextFeatureWriter() {}

        virtual bool write(const FeatureHeader& hdr,
                           const Extractor::featureArrayType& featureArray);

    };
}

#endif // TEXTFEATUREWRITER_H
