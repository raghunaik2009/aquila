/**
 * @file DtwPoint.h
 *
 * A single DTW point - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.5.7
 */

#ifndef DTWPOINT_H
#define DTWPOINT_H

#include "../global.h"

namespace Aquila
{
    /**
     * A struct representing a single point in DTW array.
     */
    struct AQUILA_EXPORT DtwPoint
    {
        DtwPoint();
        DtwPoint(unsigned int x_, unsigned int y_, double distanceLocal);

        /**
         * Coordinates of the point in the DTW array.
         */
        unsigned int x, y;

        /**
         * Local distance at this point.
         */
        double dLocal;
        /**
         * Accumulated distance at this point.
         */
        double dAccumulated;

        /**
         * Points to previous point in the DTW lowest-cost path.
         */
        DtwPoint* previous;
    };
}

#endif // DTWPOINT_H
