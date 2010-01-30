/**
 * @file ConsoleProcessingIndicator.cpp
 *
 * A console processing indicator - implementation.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.2
 * @since 2.5.2
 */

#include "ConsoleProcessingIndicator.h"


namespace Aquila
{
    /**
     * Initializes the indicator, setting value boundaries.
     *
     * Has to create boost display on heap, because we don't know
     * the range in the indicator's constructor.
     *
     * @param min minimum value
     * @param max maximum value
     */
    void ConsoleProcessingIndicator::start(int min, int max)
    {
        display = new boost::progress_display(max);
    }

    /**
     * Updates the textual progress bar.
     *
     * @param value current progress value
     */
    void ConsoleProcessingIndicator::progress(int value)
    {
        ++(*display);
    }

    /**
     * Called at the end of processing, deletes the display.
     */
    void ConsoleProcessingIndicator::stop()
    {
        delete display;
    }
}

