/**
 * @file ProcessingIndicator.h
 *
 * An interface of any progress indicator - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.3.0
 */

#ifndef PROCESSINGINDICATOR_H
#define PROCESSINGINDICATOR_H

#include "global.h"

namespace Aquila
{
    /**
     * An abstract base class ("interface") for processing indicators.
     */
    class AQUILA_EXPORT ProcessingIndicator
    {
    public:
        ProcessingIndicator() {}
        virtual ~ProcessingIndicator() {}

        /**
         * Initializes the indicator, setting value boundaries.
         *
         * @param min minimum value
         * @param max maximum value
         */
        virtual void start(int min, int max) = 0;

        /**
         * This should be called in the iteration with current progress value.
         *
         * @param value current progress value
         */
        virtual void progress(int value) = 0;

        /**
         * Called at the end of processing, deinitializes the indicator.
         */
        virtual void stop() = 0;
    };
}

#endif // PROCESSINGINDICATOR_H
