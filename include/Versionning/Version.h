//          Copyright Jeremy Coulon 2012-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/** @file */

#pragma once

//===================
//==  Versionning  ==
//===================
#include "Versionning/VersionException.h"

//=============
//==  Boost  ==
//=============
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

//===========
//==  STD  ==
//===========
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

/// Namespace of the Versionning library
namespace Vers
{
    /// Data structure to store a version number
    class Version
    {
    public:
        /// Default constructor
        /**
          * Version is initialized to v0.0.0.0
          */
        Version()
            : Version(0, 0, 0, 0)
        {
            // Empty
        }

        /// Constructor taking 4 numbers as parameters
        /**
          * @param major    1st version number
          * @param minor    2nd version number
          * @param patch    3rd version number
          * @param tweak    4th version number
          */
        Version(unsigned short major,
                unsigned short minor,
                unsigned short patch,
                unsigned short tweak)
            : major_(major),
              minor_(minor),
              patch_(patch),
              tweak_(tweak)
        {
            // Empty
        }

        /// Constructor from a string
        /**
          * @param version a string representing a version number. This string must be well formed.
          * @throw VersionException
          * @see Version::set(const std::string&)
          */
        explicit Version(const std::string& version)
        {
            set(version);
        }

        /// Get 1st version number
        unsigned short getMajor() const
        {
            return major_;
        }

        /// Get 2nd version number
        unsigned short getMinor() const
        {
            return minor_;
        }

        /// Get 3rd version number
        unsigned short getPatch() const
        {
            return patch_;
        }

        /// Get 4th version number
        unsigned short getTweak() const
        {
            return tweak_;
        }

        /// Set 1st version number
        void setMajor(unsigned short major)
        {
            major_ = major;
        }

        /// Set 2nd version number
        void setMinor(unsigned short minor)
        {
            minor_ = minor;
        }

        /// Set 3rd version number
        void setPatch(unsigned short patch)
        {
            patch_ = patch;
        }

        /// Set 4th version number
        void setTweak(unsigned short tweak)
        {
            tweak_ = tweak;
        }

        /// Set complete version number from 4 numbers
        void set(unsigned short major,
                 unsigned short minor,
                 unsigned short patch,
                 unsigned short tweak)
        {
            major_ = major;
            minor_ = minor;
            patch_ = patch;
            tweak_ = tweak;
        }

        /// Set complete version number from a string
        /**
          * The given string must be well formed.
          * It must be composed of 1 to 4 unsigned numbers separated by a dot '.' or comma ','.
          * If the string is bad formed, an exception is thrown.
          * This method provides the strong exception-safety guarantee.
          * @param version a string containing the version number
          * @throw VersionException
          */
        void set(const std::string& version)
        {
            unsigned short major, minor, patch, tweak;
            try
            {
                std::vector<std::string> splitResult;
                boost::algorithm::split(splitResult, version, boost::algorithm::is_any_of(".,"));
                // Check that we have between 1 and 4 numbers in the version string
                if (splitResult.size() == 0 || splitResult.size() > 4)
                    BOOST_THROW_EXCEPTION(VersionException());

                boost::algorithm::trim(splitResult[0]);
                major = boost::lexical_cast<unsigned short>(splitResult[0]);

                if (splitResult.size() >= 2)
                {
                    boost::algorithm::trim(splitResult[1]);
                    minor = boost::lexical_cast<unsigned short>(splitResult[1]);
                }
                else
                {
                    minor = 0;
                }

                if (splitResult.size() >= 3)
                {
                    boost::algorithm::trim(splitResult[2]);
                    patch = boost::lexical_cast<unsigned short>(splitResult[2]);
                }
                else
                {
                    patch = 0;
                }

                if (splitResult.size() == 4)
                {
                    boost::algorithm::trim(splitResult[3]);
                    tweak = boost::lexical_cast<unsigned short>(splitResult[3]);
                }
                else
                {
                    tweak = 0;
                }
            }
            catch (const VersionException& e)
            {
                e << input_version(version);
                throw;
            }
            catch (const boost::exception& /*e*/)
            {
                std::exception_ptr e_ptr = std::current_exception();
                throw VersionException() << input_version(version) << nested_exception(e_ptr);
            }
            catch (const std::exception& /*e*/)
            {
                std::exception_ptr e_ptr = std::current_exception();
                throw VersionException() << input_version(version) << nested_exception(e_ptr);
            }

            major_ = major;
            minor_ = minor;
            patch_ = patch;
            tweak_ = tweak;
        }

    private:
        unsigned short major_;
        unsigned short minor_;
        unsigned short patch_;
        unsigned short tweak_;
    };

    /// Equal operator of 2 version numbers
    /**
      * @param v1   First version number
      * @param v2   Second version number
      * @return
      *         - True if the 2 versions are equal.
      *         - False otherwise.
      */
    inline bool operator== (const Version& v1, const Version& v2)
    {
        return std::forward_as_tuple(v1.getMajor(), v1.getMinor(), v1.getPatch(), v1.getTweak()) == std::forward_as_tuple(v2.getMajor(), v2.getMinor(), v2.getPatch(), v2.getTweak());
    }

    /// Less-than operator of 2 version numbers
    /**
      * @param v1   First version number
      * @param v2   Second version number
      * @return
      *         - True if the first version number is less than the second version number.
      *         - False otherwise.
      */
    inline bool operator< (const Version& v1, const Version& v2)
    {
        return std::forward_as_tuple(v1.getMajor(), v1.getMinor(), v1.getPatch(), v1.getTweak()) < std::forward_as_tuple(v2.getMajor(), v2.getMinor(), v2.getPatch(), v2.getTweak());
    }

    /// Output stream operator
    /**
      * @param os Output stream
      * @param v  Version number
      */
    inline std::ostream& operator<<(std::ostream& os, const Version& v)
    {
        os << v.getMajor()
           << '.' << v.getMinor()
           << '.' << v.getPatch()
           << '.' << v.getTweak();
        return os;
    }

    /// Input stream operator
    /**
      * @param is Input stream
      * @param v Version number
      */
    inline std::istream& operator>>(std::istream& is, Version& v)
    {
        char separator;
        unsigned short major, minor, patch, tweak;
        is >> major >> separator >> minor >> separator >> patch >> separator >> tweak;
        v.set(major, minor, patch, tweak);
        return is;
    }
}
