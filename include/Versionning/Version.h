#pragma once

#include "Versionning/VersionException.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>

namespace Versionning
{
    class Version
    {
    public:
        /// Constructors
        //@{
        Version()
            : major_(0), minor_(0), patch_(0), tweak_(0)
        {

        }

        Version(unsigned int major, unsigned int minor, unsigned int patch, unsigned int tweak)
            : major_(major), minor_(minor), patch_(patch), tweak_(tweak)
        {

        }

        Version(const std::string& version)
        {
            setVersion(version);
        }
        //@}

        /// Getters
        //@{
        unsigned int getMajor() const
        {
            return major_;
        }

        unsigned int getMinor() const
        {
            return minor_;
        }

        unsigned int getPatch() const
        {
            return patch_;
        }

        unsigned int getTweak() const
        {
            return tweak_;
        }

        std::string getVersion() const
        {
            static const std::string separator(".");
            std::string result;
            result += boost::lexical_cast<std::string>(major_);
            result += separator;
            result += boost::lexical_cast<std::string>(minor_);
            result += separator;
            result += boost::lexical_cast<std::string>(patch_);
            result += separator;
            result += boost::lexical_cast<std::string>(tweak_);
            return result;
        }
        //@}

        /// Setters
        //@{
        void setMajor(unsigned int major)
        {
            major_ = major;
        }

        void setMinor(unsigned int minor)
        {
            minor_ = minor;
        }

        void setPatch(unsigned int patch)
        {
            patch_ = patch;
        }

        void setTweak(unsigned int tweak)
        {
            tweak_ = tweak;
        }

        void setVersion(const std::string& version)
        {
            std::vector<std::string> splitResult;
            boost::algorithm::split(splitResult, version, boost::algorithm::is_any_of(".,"));
            // Check that we have between 1 and 4 numbers in the version string
            if(splitResult.size() == 0 || splitResult.size() > 4)
                throw VersionException("Incorrect version string: " + version + " . The provided string should contains 1-4 numbers separated by '.' or ','.");

            boost::algorithm::trim(splitResult[0]);
            major_ = boost::lexical_cast<unsigned int>(splitResult[0]);

            if(splitResult.size() >= 2)
            {
                boost::algorithm::trim(splitResult[1]);
                minor_ = boost::lexical_cast<unsigned int>(splitResult[1]);
            }
            else
                minor_ = 0;

            if(splitResult.size() >= 3)
            {
                boost::algorithm::trim(splitResult[2]);
                patch_ = boost::lexical_cast<unsigned int>(splitResult[2]);
            }
            else
                patch_ = 0;

            if(splitResult.size() == 4)
            {
                boost::algorithm::trim(splitResult[3]);
                tweak_ = boost::lexical_cast<unsigned int>(splitResult[3]);
            }
            else
                tweak_ = 0;
        }
        //@}

    protected:
    private:
        unsigned int major_;
        unsigned int minor_;
        unsigned int patch_;
        unsigned int tweak_;
    };

    /// Version comparison operators
    //@{
    bool operator== (const Version& v1, const Version& v2)
    {
        return v1.getMajor() == v2.getMajor()
                && v1.getMinor() == v2.getMinor()
                && v1.getPatch() == v2.getPatch()
                && v1.getTweak() == v2.getTweak();
    }

    bool operator!= (const Version& v1, const Version& v2)
    {
        return !(v1 == v2);
    }

    bool operator< (const Version& v1, const Version& v2)
    {
        if(v1.getMajor() < v2.getMajor())
            return true;
        else if(v1.getMajor() > v2.getMajor())
            return false;
        else
        {
            if(v1.getMinor() < v2.getMinor())
                return true;
            else if(v1.getMinor() > v2.getMinor())
                return false;
            else
            {
                if(v1.getPatch() < v2.getPatch())
                    return true;
                else if(v1.getPatch() > v2.getPatch())
                    return false;
                else
                {
                    if(v1.getTweak() < v2.getTweak())
                        return true;
                    else
                        return false;
                }
            }
        }
    }

    bool operator> (const Version& v1, const Version& v2)
    {
        if(v1.getMajor() > v2.getMajor())
            return true;
        else if(v1.getMajor() < v2.getMajor())
            return false;
        else
        {
            if(v1.getMinor() > v2.getMinor())
                return true;
            else if(v1.getMinor() < v2.getMinor())
                return false;
            else
            {
                if(v1.getPatch() > v2.getPatch())
                    return true;
                else if(v1.getPatch() < v2.getPatch())
                    return false;
                else
                {
                    if(v1.getTweak() > v2.getTweak())
                        return true;
                    else
                        return false;
                }
            }
        }
    }

    bool operator<= (const Version& v1, const Version& v2)
    {
        return !(v1 > v2);
    }

    bool operator>= (const Version& v1, const Version& v2)
    {
        return !(v1 < v2);
    }
    //@}
}
