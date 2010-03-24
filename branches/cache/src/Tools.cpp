/**
 * @file Tools.cpp
 *
 * Some utility methods - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2009-2010
 * @version 2.5.0
 * @since 2.2.1
 */

#include "Tools.h"

namespace Aquila
{
    /**
     * Converts one of the WindowType enumeration values to its name.
     *
     * @param type window type as an enum
     * @return window function name
     */
    std::string Tools::windowTypeToString(WindowType type)
    {
        switch (type)
        {
        case WIN_RECT:
            return "Rectangular";
        case WIN_HAMMING:
            return "Hamming";
        case WIN_HANN:
            return "Hann";
        case WIN_BLACKMAN:
            return "Blackman";
        case WIN_BARLETT:
            return "Barlett";
        case WIN_FLATTOP:
            return "Flat-top";
        }
        return "Unknown";
    }

    /**
     * Converts window name to an enumeration value.
     *
     * If the name cannot be recognized, WIN_HAMMING is returned.
     *
     * @param name window function name
     * @return one of WindowType values
     */
    WindowType Tools::stringToWindowType(const std::string& name)
    {
        if ("Rectangular" == name)
        {
            return WIN_RECT;
        }
        else if ("Hamming" == name)
        {
            return WIN_HAMMING;
        }
        else if ("Hann" == name)
        {
            return WIN_HANN;
        }
        else if ("Blackman" == name)
        {
            return WIN_BLACKMAN;
        }
        else if ("Barlett" == name)
        {
            return WIN_BARLETT;
        }
        else if ("Flat-top" == name)
        {
            return WIN_FLATTOP;
        }

        return WIN_HAMMING;
    }
}
