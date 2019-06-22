/***********************************************************************\ 
|* Name: Ex11_08.cpp                                                   *|
|* Author: crdrisko                                                    *|
|* Date: 06/18/2019-09:58:02                                           *|
|* Description: Defining mutable member variables that can be modified *|
|*  within const member functions                                      *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Ex11_08.cpp Box.cpp -o Ex11_08.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include "Box.hpp"

int main()
{
    Box myBox {3.0, 4.0, 5.0};
    myBox.printVolume();

    myBox.setHeight(55.5);
    myBox.printVolume();

    // Even for constant Boxes mutable member variables can be modified:
    const Box constBox {1.0, 2.0, 3.0};
    constBox.printVolume();
    constBox.printVolume();
}
