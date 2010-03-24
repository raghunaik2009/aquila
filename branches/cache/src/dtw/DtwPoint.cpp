/**
 * @file DtwPoint.cpp
 *
 * A single DTW point - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.5.7
 */

#include "DtwPoint.h"

namespace Aquila
{
    /**
     * Creates the point with default values.
     */
    DtwPoint::DtwPoint():
        x(0), y(0), dLocal(0.0), dAccumulated(0.0), previous(0)
    {
    }

    /**
     * Creates the point and associates it with given coordinates.
     *
     * @param x_ x coordinate in DTW array
     * @param y_ y coordinate in DTW array
     * @param distanceLocal value of local distance at point (x, y)
     */
    DtwPoint::DtwPoint(unsigned int x_, unsigned int y_, double distanceLocal):
        x(x_), y(y_), dLocal(distanceLocal), dAccumulated(0.0), previous(0)
    {
        if (0 ==x || 0 == y)
            dAccumulated = dLocal;
    }
}
