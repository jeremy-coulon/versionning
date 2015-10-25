//          Copyright Jeremy Coulon 2012-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//===================
//==  Versionning  ==
//===================
#include "Versionning/Version.h"

//=============
//==  Boost  ==
//=============
#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>

//===========
//==  STD  ==
//===========
#include <sstream>

BOOST_AUTO_TEST_SUITE(StringConversions)

BOOST_AUTO_TEST_CASE(CorrectInputString)
{
    const std::string str("0.3.5.0");
    Vers::Version v1(0, 3, 5, 0);
    Vers::Version v2(str);
    Vers::Version v3;

    std::stringstream sstream;
    sstream << str;
    sstream >> v3;

    BOOST_CHECK_EQUAL(v1, v2);
    BOOST_CHECK_EQUAL(v1, v3);
}

BOOST_AUTO_TEST_CASE(IncorrectInputString)
{
    Vers::Version v1(0, 3, 5, 0);
    Vers::Version v2(0, 3, 5, 0);

    BOOST_CHECK_THROW(v1.set(""), Vers::VersionException);
    BOOST_CHECK_THROW(v1.set("0.3.zzz"), Vers::VersionException);

    // Check that v1 remains the same (strong exception-safety guarantee).
    BOOST_CHECK_EQUAL(v1, v2);
}

BOOST_AUTO_TEST_CASE(OutputString)
{
    Vers::Version v1(0, 3, 5, 0);
    std::string v2("0.3.5.0");

    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(v1), v2);
}

BOOST_AUTO_TEST_SUITE_END()
