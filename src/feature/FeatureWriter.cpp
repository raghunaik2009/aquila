/**
 * @file FeatureWriter.cpp
 *
 * Feature writer interface - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#include "FeatureWriter.h"

namespace Aquila
{
    /**
     * Creates the writer object and assigns filename.
     *
     * @param filename full path to output file
     */
    FeatureWriter::FeatureWriter(const std::string& filename):
        m_filename(filename)
    {
    }

    /**
     * Deletes the writer.
     */
    FeatureWriter::~FeatureWriter()
    {
    }
}
