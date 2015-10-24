//          Copyright Jeremy Coulon 2012-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/** @file */

#pragma once

//=============
//==  Boost  ==
//=============
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>

//===========
//==  STD  ==
//===========
#include <exception>
#include <string>

/// Namespace of the Versionning library
namespace Vers
{
    /// Exception type that can be thrown when using the Versionning library
    /**
      * @note This struct inherits from boost::exception.
      * See Boost Exception library documentation at:
      * http://www.boost.org/doc/libs/release/libs/exception/doc/boost-exception.html
      */
    struct VersionException : virtual std::exception, virtual boost::exception
    {
    };

    /// VersionException additional information: input version string
    typedef boost::error_info<struct tag_input_version, std::string> input_version;

    /// VersionException additional information: nested exception
    typedef boost::error_info<struct tag_nested_exception, std::exception_ptr> nested_exception;
}
