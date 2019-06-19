/***********************************************************************\ 
|* Name: Ex11_07.cpp                                                   *|
|* Author: crdrisko                                                    *|
|* Date: 06/18/2019-09:25:52                                           *|
|* Description: Overloaded const and non-const member functions        *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Ex11_07.cpp Box.cpp -o Ex11_07.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include "Box.hpp"

int main()
{
    Box box;
    box.length() = 2;                                   // References can be used to the right of an assignment
    std::cout << box.length() << std::endl;             // Prints 2

    const Box constBox;
    // constBox.length = 2;                             // Does not compile: good!
    std::cout << constBox.length() << std::endl;        // Prints 1
}
