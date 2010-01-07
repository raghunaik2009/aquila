/**
 * @file Dtw.cpp
 *
 * DTW distance calculation - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.5.7
 */

#include "Dtw.h"

#include <cmath>

namespace Aquila
{
    distanceFunction Dtw::distanceFunctions[] = {euclideanDistance,
                                                 manhattanDistance,
                                                 chebyshevDistance,
                                                 minkowskiDistance};

    /**
     * Creates the DTW object and sets signal feature object.
     *
     * @param signal feature extractor object
     */
    Dtw::Dtw(const Extractor* signal):
        from(signal), points(signal->getFramesCount()), distanceFn(euclideanDistance),
        passType(Neighbors)
    {
    }

    /**
     * Computes the DTW distance between signal and pattern.
     *
     * @param pattern feature extractor object for the pattern
     * @param normalization normalization type (default by diagonal)
     * @return double DTW distance
     */
    double Dtw::getDistance(const Extractor* pattern, NormalizationType normalization)
    {
        calculateLocalDistances(pattern);
        unsigned int signalSize = from->getFramesCount();
        unsigned int patternSize = pattern->getFramesCount();
        DtwPoint *top = 0, *center = 0, *bottom = 0, *previous = 0;

        for (unsigned int i = 1; i < signalSize; ++i)
        {
            for (unsigned int j = 1; j < patternSize; ++j)
            {
                center = &points[i - 1][j - 1];
                if (Neighbors == passType)
                {
                    top = &points[i - 1][j];
                    bottom = &points[i][j - 1];
                }
                else // Diagonals
                {
                    if (i > 1 && j > 1)
                    {
                        top = &points[i - 2][j - 1];
                        bottom = &points[i - 1][j - 2];
                    }
                    else
                    {
                        top = &points[i - 1][j];
                        bottom = &points[i][j - 1];
                    }
                }

                if (top->dAccumulated < center->dAccumulated)
                    previous = top;
                else
                    previous = center;

                if (bottom->dAccumulated < previous->dAccumulated)
                    previous = bottom;

                points[i][j].dAccumulated = points[i][j].dLocal + previous->dAccumulated;
                points[i][j].previous = previous;
            }
        }

        double distance = points[signalSize - 1][patternSize - 1].dAccumulated;

        switch (normalization)
        {
        case Diagonal:
            distance /= std::sqrt(signalSize*signalSize + patternSize*patternSize);
            break;
        case SumOfSides:
            distance /= signalSize + patternSize;
            break;
        case NoNormalization:
        default:
            break;
        }

        return distance;
    }

    /**
     * Calculates local distances array.
     *
     * @param pattern feature extractor object of the pattern
     */
    void Dtw::calculateLocalDistances(const Extractor* pattern)
    {
        unsigned int patternSize = pattern->getFramesCount();
        for (unsigned int i = 0; i < from->getFramesCount(); ++i)
        {
            points[i].resize(patternSize);
            for (unsigned int j = 0; j < patternSize; j++)
                points[i][j] = DtwPoint(i, j, distanceFn(from->getVector(i), pattern->getVector(j)));
        }
    }

    /**
     * Chooses a distance function.
     *
     * @param index function index in the distanceFunctions array
     */
    void Dtw::setDistanceFunction(int index)
    {
        int functionsCount = sizeof(distanceFunctions)/sizeof(distanceFunctions[0]);
        if (index > 0 && index < functionsCount)
        {
            distanceFn = distanceFunctions[index];
        }
    }

    /**
     * Returns the lowest-cost path in the DTW array.
     *
     * @return path
     */
    DtwPath Dtw::getPath()
    {
        DtwPath path;

        int width = points.size(), height = points[0].size();

        DtwPoint* point = &points[width-1][height - 1];

        while(point->previous != 0)
        {
            path.push_back(std::make_pair(point->x, point->y));
            point = point->previous;
        }

        return path;
    }
}
