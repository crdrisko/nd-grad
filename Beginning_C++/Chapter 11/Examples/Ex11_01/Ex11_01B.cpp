/*************************************************************************\ 
|* Name: Ex11_01B.cpp                                                    *|
|* Author: crdrisko                                                      *|
|* Date: 06/13/2019-12:41:00                                             *|
|* Description: Defining functions and constructors outside the class    *|
|*  definition                                                           *|
|*                                                                       *|
|*                                                                       *|
|* Complile Command: g++ Ex11_01B.cpp Box.cpp -o Ex11_01B.out -std=c++17 *|
\*************************************************************************/

#include <iostream>
#include "Box.hpp"

int main()
{
    Box firstBox {80.0, 50.0, 40.0};                // Create a box
    double firstBoxVolume {firstBox.volume()};      // Calculate the box volume
    std::cout << "Volume of the first Box object is " << firstBoxVolume << std::endl;

    Box secondBox;                                  // Uses compiler-generated default constructor
    double secondBoxVolume {secondBox.volume()};    // Calculate the box volume
    std::cout << "Volume of the second Box object is " << secondBoxVolume << std::endl;
}
