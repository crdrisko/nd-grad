/***********************************************************************\ 
|* Name: Ex11_04.cpp                                                   *|
|* Author: crdrisko                                                    *|
|* Date: 06/15/2019-16:29:15                                           *|
|* Description: Adding public getters and setters for private member   *|
|*  variables                                                          *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Ex11_04.cpp Box.cpp -o Ex11_04.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include "Box.hpp"

int main()
{
    Box myBox {3.0, 4.0, 5.0};
    std::cout << "myBox dimensions are " << myBox.getLength()
              << " by " << myBox.getWidth()
              << " by " << myBox.getHeight() << std::endl;

    myBox.setLength(-20);                                               // Ignored!
    myBox.setWidth(40.0);
    myBox.setHeight(10.0);
    std::cout << "myBox dimensions are now " << myBox.getLength()       // 3 (unchanged)
              << " by " << myBox.getWidth()                             // by 40
              << " by " << myBox.getHeight() << std::endl;              // by 10
}
