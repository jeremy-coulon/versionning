
//          Copyright Jeremy Coulon 2012.
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
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ComparisonOperator)

BOOST_AUTO_TEST_CASE(Equal)
{
    Vers::Version v1(0, 3, 5, 0);
    Vers::Version v2(0, 3, 5, 0);
    Vers::Version v3(0, 3, 6, 0);

    BOOST_CHECK(v1 == v2);
    BOOST_CHECK(! (v1 == v3));
}

BOOST_AUTO_TEST_CASE(NotEqual)
{
    Vers::Version v1(0, 3, 5, 0);
    Vers::Version v2(0, 3, 5, 0);
    Vers::Version v3(0, 3, 6, 0);

    BOOST_CHECK(v1 != v3);
    BOOST_CHECK(! (v1 != v2));
}

BOOST_AUTO_TEST_CASE(LessThan)
{
    Vers::Version v1(0, 3, 5, 0);
    Vers::Version v2(0, 3, 5, 0);
    Vers::Version v3(0, 3, 6, 0);
    Vers::Version v4(0, 3, 4, 0);

    BOOST_CHECK(!(v1 < v2));
    BOOST_CHECK(v1 < v3);
    BOOST_CHECK(!(v1 < v4));
}

BOOST_AUTO_TEST_CASE(GreaterThan)
{
    Vers::Version v1(0, 3, 5, 0);
    Vers::Version v2(0, 3, 5, 0);
    Vers::Version v3(0, 3, 6, 0);
    Vers::Version v4(0, 3, 4, 0);

    BOOST_CHECK(!(v1 > v2));
    BOOST_CHECK(!(v1 > v3));
    BOOST_CHECK((v1 > v4));
}

BOOST_AUTO_TEST_CASE(LessOrEqual)
{
    Vers::Version v1(0, 3, 5, 0);
    Vers::Version v2(0, 3, 5, 0);
    Vers::Version v3(0, 3, 6, 0);
    Vers::Version v4(0, 3, 4, 0);

    BOOST_CHECK(v1 <= v2);
    BOOST_CHECK(v1 <= v3);
    BOOST_CHECK(!(v1 <= v4));
}

BOOST_AUTO_TEST_CASE(GreaterOrEqual)
{
    Vers::Version v1(0, 3, 5, 0);
    Vers::Version v2(0, 3, 5, 0);
    Vers::Version v3(0, 3, 6, 0);
    Vers::Version v4(0, 3, 4, 0);

    BOOST_CHECK((v1 >= v2));
    BOOST_CHECK(!(v1 >= v3));
    BOOST_CHECK((v1 >= v4));
}

BOOST_AUTO_TEST_SUITE_END()
