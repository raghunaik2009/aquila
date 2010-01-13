/**
 * @file global.h
 *
 * Global constants, typedefs and macros.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 2.4.1
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <complex>
#include <string>
#include <vector>


#ifdef AQUILA_DLL
#if defined(AQUILA_MAKEDLL)
#define AQUILA_EXPORT  __declspec(dllexport)
#else
#define AQUILA_EXPORT  __declspec(dllimport)
#endif
#endif

#ifndef AQUILA_EXPORT
#define AQUILA_EXPORT
#endif


/**
 * Main library namespace.
 */
namespace Aquila
{
    /**
     * Library version.
     */
    const std::string VERSION = "2.5.1";

    /**
     * Total count of Mel frequency scale filters.
     */
    const unsigned int MELFILTERS = 24;

    /**
     * Our standard complex number type, using double precision.
     */
    typedef std::complex<double> cplx;

    /**
     * Spectrum type - a vector of complex values.
     */
    typedef std::vector<cplx> spectrumType;
}

#endif // GLOBAL_H
