/**
 * @file Exceptions.h
 *
 * Exception class definitions.
 *
 * Aquila defines its own base class which inherits std::runtime_error,
 * all exceptions thrown by the library inherit Aquila::Exception.
 *
 * @author Zbigniew Siciarz
 * @date 2009-2010
 * @version 2.5.0
 * @since 2.0.0
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include "global.h"
#include <stdexcept>
#include <string>

namespace Aquila
{
    /**
     * Base exception class of the library.
     *
     * Class clients should rather catch exceptions of specific types, such as
     * Aquila::FormatException, however it is allowed to catch Aquila::Exception
     * as the last resort (but catch(...)).
     */
    class AQUILA_EXPORT Exception : public std::runtime_error
	{
	public:
	    /**
         * Creates an exception object.
	     *
         * @param what exception message
	     */
		Exception(const std::string& what):
			runtime_error(what)
		{
		}
	};


	/**
     * Data format-related exception.
	 *
	 */
    class AQUILA_EXPORT FormatException : public Exception
	{
	public:
        /**
         * Creates a data format exception object.
         *
         * @param what exception message
         */
	    FormatException(const std::string& what):
			Exception(what)
		{
		}
	};
}

#endif /* EXCEPTIONS_H_ */
