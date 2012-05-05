
//          Copyright Jeremy Coulon 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <boost/exception/all.hpp>

#include <stdexcept>
#include <string>

namespace Versionning
{
    struct VersionException : virtual std::runtime_error, virtual boost::exception
    {
        VersionException(const std::string& msg)
            : std::runtime_error(msg)
        {

        }
    };
}
