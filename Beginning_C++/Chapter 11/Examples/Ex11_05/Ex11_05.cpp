/***********************************************************************\ 
|* Name: Ex11_05.cpp                                                   *|
|* Author: crdrisko                                                    *|
|* Date: 06/15/2019-17:10:30                                           *|
|* Description: Allowing method chaining by returning a reference to   *| 
|*  this                                                               *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Ex11_05.cpp Box.cpp -o Ex11_05.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include "Box.hpp"

int main()
{
    Box myBox {3.0, 4.0, 5.0};
    std::cout << "myBox dimensions are " << myBox.getLength()
              << " by " << myBox.getWidth()
              << " by " << myBox.getHeight() << std::endl;

    // Method chaining: set all dimensions of a box in one statement:
    myBox.setLength(-20.0).setWidth(40.0).setHeight(10.0);
    std::cout << "myBox dimensions are now " << myBox.getLength()       // 3 (unchanged)
              << " by " << myBox.getWidth()                             // by 40
              << " by " << myBox.getHeight() << std::endl;              // by 10
}
