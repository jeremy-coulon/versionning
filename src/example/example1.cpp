
//          Copyright Jeremy Coulon 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//===================
//==  Versionning  ==
//===================
#include "Versionning/Version.h"

//===========
//==  STD  ==
//===========
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
    Vers::Version v1(1, 3, 5, 8);
    Vers::Version v2(1, 3, 7, 2);

    if(v1 < v2)
        std::cout << "Version v" << v1 << " is less than version v" << v2 << std::endl;

    return 0;
}
