/**
 * @file functions.cpp
 *
 * DTW distance functions - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.5.7
 */

#include "functions.h"

#include <cmath>

namespace Aquila
{
    /**
     * Returns Euclidean distance between two vectors.
     *
     * @param v1 first vector
     * @param v2 second vector
     * @return Euclidean distance
     */
    double euclideanDistance(const std::vector<double>& v1, const std::vector<double>& v2)
    {
        double d = 0.0;
        for (unsigned int i = 0; i < v1.size(); i++)
            d += (v1[i] - v2[i])*(v1[i] - v2[i]);
        return std::sqrt(d);
    }

    /**
     * Returns Manhattan (taxicab) distance between two vectors.
     *
     * @param v1 first vector
     * @param v2 second vector
     * @return Manhattan distance
     */
    double manhattanDistance(const std::vector<double>& v1, const std::vector<double>& v2)
    {
        double d = 0.0;
        for (unsigned int i = 0; i < v1.size(); i++)
            d += std::abs(v1[i] - v2[i]);
        return d;
    }

    /**
     * Returns Chebyshev distance between two vectors.
     *
     * @param v1 first vector
     * @param v2 second vector
     * @return Chebyshev distance
     */
    double chebyshevDistance(const std::vector<double>& v1, const std::vector<double>& v2)
    {
        double d = 0.0, max = 0.0;
        for (unsigned int i = 0; i < v1.size(); i++)
        {
            d = std::abs(v1[i] - v2[i]);
            if (d > max)
                max = d;
        }
        return max;
    }

    /**
     * Returns Minkowski distance (with p = 0.33) between two vectors.
     *
     * @param v1 first vector
     * @param v2 second vector
     * @return Minkowski distance
     */
    double minkowskiDistance(const std::vector<double>& v1, const std::vector<double>& v2)
    {
        double d = 0.0, p = 0.33;
        for (unsigned int i = 0; i < v1.size(); i++)
            d += std::pow(std::abs(v1[i] - v2[i]), p);

        return std::pow(d, 1.0/p);
    }
}
