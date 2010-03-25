/**
 * @file TextFeatureWriter.cpp
 *
 * A simple text writer - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#include "TextFeatureWriter.h"

#include "../global.h"
#include "../Exceptions.h"
#include <fstream>

namespace Aquila
{

    /**
     * Writes the header and data to a plain text file.
     *
     * @param hdr const reference to feature header
     * @param featureArray const reference to feature data array
     */
    bool TextFeatureWriter:: write(const FeatureHeader& hdr,
                                   const Extractor::featureArrayType& featureArray)
    {
        if (featureArray.empty())
        {
            throw Exception("Empty feature array!");
        }

        std::ofstream ofs(m_filename.c_str());
        ofs << "# Generated with: Aquila v. " << VERSION << "\n" <<
               "# Original wave file: "       << hdr.wavFilename << "\n" <<
               "# Audio sampling frequency: " << "?????" << "\n" <<
               "# Frame length: "             << hdr.frameLength << "\n" <<
               "# Frames count: "             << featureArray.size() << "\n" <<
               "# Parameters type: "          << hdr.type << "\n" <<
               "# Parameters per frame: "     << hdr.paramsPerFrame << "\n" <<
               "# Save timestamp: "           << hdr.timestamp<< "\n";
        ofs.precision(13);
        for (unsigned int i = 0, size = featureArray.size(); i < size; ++i)
        {
            ofs << "#frame: " << i << "\n";
            for (unsigned int j = 0; j < hdr.paramsPerFrame; ++j)
            {
                ofs << featureArray[i][j] << "\n";
            }
        }
        ofs.close();

        return true;
    }
}
