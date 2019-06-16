/***********************************************************************\ 
|* Name: Ex11_06.cpp                                                   *|
|* Author: crdrisko                                                    *|
|* Date: 06/16/2019-16:26:56                                           *|
|* Description: Defining const member functions that can be called on  *|
|*  const objects                                                      *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Ex11_06.cpp Box.cpp -o Ex11_06.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include "Box.hpp"

int main()
{
    const Box myBox {3.0, 4.0, 5.0};
    std::cout << "myBox dimensions are " << myBox.getLength()
              << " by " << myBox.getWidth()
              << " by " << myBox.getHeight() << std::endl;

/*  // The setters are not const, so they cannot be called on myBox
    myBox.setLength(-20.0);
    myBox.setWidth(40.0);
    myBox.setHeight(10.0);
*/

    // To call setters, you need to define a non-const object
    Box anotherBox;
    anotherBox.setLength(3.0);
    anotherBox.setWidth(4.0);
    anotherBox.setHeight(5.0);
    std::cout << "anotherBox dimensions are " << anotherBox.getLength()
              << " by " << anotherBox.getWidth()
              << " by " << anotherBox.getHeight() << std::endl;
}
