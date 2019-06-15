/***********************************************************************\ 
|* Name: Ex11_03.cpp                                                   *|
|* Author: crdrisko                                                    *|
|* Date: 06/13/2019-15:29:50                                           *|
|* Description: Using a delegating constructor                         *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Ex11_03.cpp Box.cpp -o Ex11_03.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include "Box.hpp"

int main()
{
    Box box1 {2.0, 3.0, 4.0};               // An arbitrary box
    Box box2 {5.0};
    std::cout << "box1 volume = " << box1.volume() << std::endl;
    std::cout << "box2 volume = " << box2.volume() << std::endl;
}
