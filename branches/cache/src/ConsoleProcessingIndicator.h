/**
 * @file ConsoleProcessingIndicator.h
 *
 * A console processing indicator - header.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.2
 * @since 2.5.2
 */

#ifndef CONSOLEPROCESSINGINDICATOR_H
#define CONSOLEPROCESSINGINDICATOR_H

#include "ProcessingIndicator.h"
#include <boost/progress.hpp>

namespace Aquila
{
    /**
     * A simple textual processing indicator using boost::progress_display.
     */
    class AQUILA_EXPORT ConsoleProcessingIndicator : public ProcessingIndicator
    {
    public:
        /**
         * Creates the processing indicator.
         */
        ConsoleProcessingIndicator():
            display(0)
        {
        }

        void start(int min, int max);

        void progress(int value);

        void stop();

    private:
        /**
         * Boost object.
         */
        boost::progress_display* display;
    };
}

#endif // CONSOLEPROCESSINGINDICATOR_H
