
//          Copyright Jeremy Coulon 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/**
  * @file
  *
  * @mainpage
  * @author Jeremy Coulon
  * @date 2012
  *
  * @section Introduction
  *
  * This C++ library contains a simple portable data structure to store versionning information of a project.\n
  * It allows you to store information about your library being in version vX.Y.Z.T.\n
  * It is particularly useful for comparing version number.
  * For example to know if version vX.Y.Z.T is greater than v3.12.0.0.\n
  *
  * A version number consists of 4 unsigned numbers :
  * @li The first number is called 'Major' number.
  * @li The second number is called 'Minor' number.
  * @li The third number is called 'Patch' number.
  * @li The fourth (last) number is called 'Tweak' number.
  *
  * @section Installation
  *
  * This library is a header-only library. That means you don't need to compile anything to use it in your own project. You can just write :
  * @code
  * #include <Versionning/Version.h>
  * @endcode
  *
  * @section License
  *
  *          Copyright Jeremy Coulon 2012.\n
  * Distributed under the Boost Software License, Version 1.0.\n
  *   (See accompanying file <a href="../LICENSE_1_0.txt">LICENSE_1_0.txt</a> or copy at\n
  *         http://www.boost.org/LICENSE_1_0.txt)
  *
  * \example example.cpp
  * This is an example of how to compare 2 version numbers.
  * Output : \verbatim Version v1.3.5.8 is less than version v1.3.7.2 \endverbatim
  *
  */

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
            : major_(0), minor_(0), patch_(0), tweak_(0)
        {

        }

        /// Constructor taking 4 numbers as parameters
        /**
          * @param major    1st version number
          * @param minor    2nd version number
          * @param patch    3rd version number
          * @param tweak    4th version number
          */
        Version(unsigned short major, unsigned short minor, unsigned short patch, unsigned short tweak)
            : major_(major), minor_(minor), patch_(patch), tweak_(tweak)
        {

        }

        /// Constructor from a string
        /**
          * @param version a string representing a version number. This string must be well formed.
          * @throw VersionException
          * @see set(const std::string&)
          */
        Version(const std::string& version)
        {
            set(version);
        }

        /// @name Getters
        ///@{

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

        /// Get complete version number as a string
        std::string toString() const
        {
            const std::string stringSeparator(".");
            std::string result;
            result += boost::lexical_cast<std::string>(major_);
            result += stringSeparator;
            result += boost::lexical_cast<std::string>(minor_);
            result += stringSeparator;
            result += boost::lexical_cast<std::string>(patch_);
            result += stringSeparator;
            result += boost::lexical_cast<std::string>(tweak_);
            return result;
        }

        ///@}

        /// @name Setters
        ///@{

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
        void set(unsigned short major, unsigned short minor, unsigned short patch, unsigned short tweak)
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
                if(splitResult.size() == 0 || splitResult.size() > 4)
                    BOOST_THROW_EXCEPTION(VersionException());

                boost::algorithm::trim(splitResult[0]);
                major = boost::lexical_cast<unsigned short>(splitResult[0]);

                if(splitResult.size() >= 2)
                {
                    boost::algorithm::trim(splitResult[1]);
                    minor = boost::lexical_cast<unsigned short>(splitResult[1]);
                }
                else
                    minor = 0;

                if(splitResult.size() >= 3)
                {
                    boost::algorithm::trim(splitResult[2]);
                    patch = boost::lexical_cast<unsigned short>(splitResult[2]);
                }
                else
                    patch = 0;

                if(splitResult.size() == 4)
                {
                    boost::algorithm::trim(splitResult[3]);
                    tweak = boost::lexical_cast<unsigned short>(splitResult[3]);
                }
                else
                    tweak = 0;
            }
            catch(const VersionException& e)
            {
                e << input_version(version);
                throw;
            }
            catch(const boost::exception& /*e*/)
            {
                boost::exception_ptr e_ptr = boost::current_exception();
                throw VersionException() << input_version(version) << nested_exception(e_ptr);
            }
            catch(const std::exception& /*e*/)
            {
                boost::exception_ptr e_ptr = boost::current_exception();
                throw VersionException() << input_version(version) << nested_exception(e_ptr);
            }

            major_ = major;
            minor_ = minor;
            patch_ = patch;
            tweak_ = tweak;
        }

        ///@}

    private:
        unsigned short major_;
        unsigned short minor_;
        unsigned short patch_;
        unsigned short tweak_;

        // Frienship
        friend bool operator==(const Version& v1, const Version& v2);
        friend bool operator!=(const Version& v1, const Version& v2);
        friend bool operator< (const Version& v1, const Version& v2);
        friend bool operator> (const Version& v1, const Version& v2);
        friend bool operator<=(const Version& v1, const Version& v2);
        friend bool operator>=(const Version& v1, const Version& v2);
        friend std::ostream& operator<<(std::ostream& os, const Version& v);
        friend std::istream& operator>>(std::istream& is, Version& v);
    };

    /// Equal operator of 2 version numbers
    /**
      * @param v1   First version number
      * @param v2   Second version number
      * @return True if the 2 versions are equal. False otherwise.
      */
    inline bool operator== (const Version& v1, const Version& v2)
    {
        return v1.major_ == v2.major_
                && v1.minor_ == v2.minor_
                && v1.patch_ == v2.patch_
                && v1.tweak_ == v2.tweak_;
    }

    /// Not-Equal operator of 2 version numbers
    /**
      * @param v1   First version number
      * @param v2   Second version number
      * @return True if the 2 versions are different. False otherwise.
      */
    inline bool operator!= (const Version& v1, const Version& v2)
    {
        return !(v1 == v2);
    }

    /// Less-than operator of 2 version numbers
    /**
      * @param v1   First version number
      * @param v2   Second version number
      * @return True if the first version number is less than the second version number. False otherwise.
      */
    inline bool operator< (const Version& v1, const Version& v2)
    {
        if(v1.major_ < v2.major_)
            return true;
        else if(v1.major_ > v2.major_)
            return false;
        else
        {
            if(v1.minor_ < v2.minor_)
                return true;
            else if(v1.minor_ > v2.minor_)
                return false;
            else
            {
                if(v1.patch_ < v2.patch_)
                    return true;
                else if(v1.patch_ > v2.patch_)
                    return false;
                else
                {
                    if(v1.tweak_ < v2.tweak_)
                        return true;
                    else
                        return false;
                }
            }
        }
    }

    /// Greater-than operator of 2 version numbers
    /**
      * @param v1   First version number
      * @param v2   Second version number
      * @return True if the first version number is greater than the second version number. False otherwise.
      */
    inline bool operator> (const Version& v1, const Version& v2)
    {
        if(v1.major_ > v2.major_)
            return true;
        else if(v1.major_ < v2.major_)
            return false;
        else
        {
            if(v1.minor_ > v2.minor_)
                return true;
            else if(v1.minor_ < v2.minor_)
                return false;
            else
            {
                if(v1.patch_ > v2.patch_)
                    return true;
                else if(v1.patch_ < v2.patch_)
                    return false;
                else
                {
                    if(v1.tweak_ > v2.tweak_)
                        return true;
                    else
                        return false;
                }
            }
        }
    }

    /// Less-or-equal operator of 2 version numbers
    /**
      * @param v1   First version number
      * @param v2   Second version number
      * @return True if the first version number is less than or equal to the second version number. False otherwise.
      */
    inline bool operator<= (const Version& v1, const Version& v2)
    {
        return !(v1 > v2);
    }

    /// Greater-or-equal operator of 2 version numbers
    /**
      * @param v1   First version number
      * @param v2   Second version number
      * @return True if the first version number is greater than or equal to the second version number. False otherwise.
      */
    inline bool operator>= (const Version& v1, const Version& v2)
    {
        return !(v1 < v2);
    }

    /// Output stream operator
    /**
      * @param os Output stream
      * @param v  Version number
      */
    inline std::ostream& operator<<(std::ostream& os, const Version& v)
    {
        const std::string stringSeparator(".");
        os << v.major_ << stringSeparator << v.minor_ << stringSeparator << v.patch_ << stringSeparator << v.tweak_;
        return os;
    }

    /// Input stream operator
    /**
      * @param is Input stream
      * @param v Version number
      */
    inline std::istream& operator>>(std::istream& is, Version& v)
    {
        std::string s;
        is >> s;
        v.set(s);
        return is;
    }

}

