/***********************************************************************\ 
|* Name: Ex11_09.cpp                                                   *|
|* Author: crdrisko                                                    *|
|* Date: 06/18/2019-12:52:23                                           *|
|* Description: Using a friend function of a class                     *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Ex11_09.cpp Box.cpp -o Ex11_09.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <memory>
#include "Box.hpp"

int main()
{
    Box box1 {2.2, 1.1, 0.5};                                           // An arbitrary box
    Box box2;                                                           // A default box
    auto box3 = std::make_unique<Box>(15.0, 20.0, 8.0);                 // Dynamically allocated box

    std::cout << "Volume of box1 = " << box1.volume() << std::endl;
    std::cout << "Surface area of box1 = " << surfaceArea(box1) << std::endl;

    std::cout << "Volume of box2 = " << box2.volume() << std::endl;
    std::cout << "Surface area of box2 = " << surfaceArea(box2) << std::endl;
 
    std::cout << "Volume of box3 = " << box3->volume() << std::endl;
    std::cout << "Surface area of box3 = " << surfaceArea(*box3) << std::endl;
}

// Friend function to calculate the surface area of a Box object
double surfaceArea(const Box& aBox)
{
    return 2.0 * (aBox.length * aBox.width + aBox.length * aBox.height + aBox.height * aBox.width);
}
