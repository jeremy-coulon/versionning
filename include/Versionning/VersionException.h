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
