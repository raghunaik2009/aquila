/**
 * @file Dtw.h
 *
 * DTW distance calculation - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.5.7
 */

#ifndef DTW_H
#define DTW_H

#include "../global.h"
#include "DtwPoint.h"
#include "functions.h"
#include "../feature/Extractor.h"
#include <list>
#include <utility>
#include <vector>

namespace Aquila
{
    /**
     * Type of DTW point array.
     */
    typedef std::vector<std::vector<DtwPoint> > dtwPointsArray;

    /**
     * Distance function prototype.
     */
    typedef double(*distanceFunction)(const std::vector<double>&, const std::vector<double>&);

    /**
     * Type of a DTW path point.
     */
    typedef std::pair<unsigned int, unsigned int> DtwPathPoint;

    /**
     * Typ of a DTW path.
     */
    typedef std::list<DtwPathPoint> DtwPath;

    /**
     * Class calculating distance between two feature objects using DTW.
     */
    class AQUILA_EXPORT Dtw
    {
    public:
        /**
         * Normalization type of result distance.
         */
        enum NormalizationType { NoNormalization, Diagonal, SumOfSides };

        /**
         * Type of lowest-cost passes between points.
         */
        enum PassType { Neighbors = 0, Diagonals = 1 };


        Dtw(const Extractor* signal);

        double getDistance(const Extractor* pattern,
                           NormalizationType normalization = Diagonal);

        /**
         * Returns a const reference to DTW point array.
         *
         * @return DTW point array
         */
        const dtwPointsArray& getPoints() { return points; }

        void setDistanceFunction(int index);

        /**
         * Sets the pass type.
         *
         * @param type pass type
         */
        void setPassType(PassType type) { passType = type; }

        DtwPath getPath();

    private:
        /**
         * An array of pointers to distance functions.
         */
        static distanceFunction distanceFunctions[];

        void calculateLocalDistances(const Extractor* pattern);

        /**
         * Extractor object for an input signal.
         */
        const Extractor* from;

        /**
         * DTW point array.
         */
        dtwPointsArray points;

        /**
         * Pointer to currently used distance function.
         */
        distanceFunction distanceFn;

        /**
         * Current type of passes between points.
         */
        PassType passType;
    };
}

#endif // DTW_H
