/**
 * @file functions.h
 *
 * DTW distance functions - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.5.7
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../global.h"
#include <vector>

namespace Aquila
{
    AQUILA_EXPORT double euclideanDistance(const std::vector<double>& v1, const std::vector<double>& v2);

    AQUILA_EXPORT double manhattanDistance(const std::vector<double>& v1, const std::vector<double>& v2);

    AQUILA_EXPORT double chebyshevDistance(const std::vector<double>& v1, const std::vector<double>& v2);

    AQUILA_EXPORT double minkowskiDistance(const std::vector<double>& v1, const std::vector<double>& v2);
}

#endif // FUNCTIONS_H
