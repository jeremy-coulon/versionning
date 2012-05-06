
//          Copyright Jeremy Coulon 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/** @file */

#pragma once

//=============
//==  Boost  ==
//=============
#include <boost/exception/exception.hpp>

//===========
//==  STD  ==
//===========
#include <stdexcept>
#include <string>

/// Namespace of the Versionning library
namespace Versionning
{
    /// Exception type that can be thrown when using the Versionning library
    /**
      * @note This struct inherits from boost::exception.
      * See Boost Exception library documentation at http://www.boost.org/doc/libs/1_49_0/libs/exception/doc/boost-exception.html
      */
    struct VersionException : virtual std::runtime_error, virtual boost::exception
    {
        /// Constructor
        /**
          * @param  msg a message string describing the exception
          */
        VersionException(const std::string& msg)
            : std::runtime_error(msg)
        {

        }

        /// Destructor
        virtual ~VersionException() throw()
        {

        }
    };
}
