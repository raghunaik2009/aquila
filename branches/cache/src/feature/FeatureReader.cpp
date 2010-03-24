/**
 * @file FeatureReader.cpp
 *
 * Feature reader interface - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#include "FeatureReader.h"

namespace Aquila
{
    /**
     * Creates the reader object and assigns filename.
     *
     * @param filename full path to input file
     */
    FeatureReader::FeatureReader(const std::string& filename):
        m_filename(filename)
    {
    }

    /**
     * Deletes the reader.
     */
    FeatureReader::~FeatureReader()
    {
    }
}
