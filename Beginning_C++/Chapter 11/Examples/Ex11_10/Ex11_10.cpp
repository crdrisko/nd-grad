/***********************************************************************\ 
|* Name: Ex11_10.cpp                                                   *|
|* Author: crdrisko                                                    *|
|* Date: 06/18/2019-13:15:57                                           *|
|* Description: Creating an array of objects                           *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Ex11_10.cpp Box.cpp -o Ex11_10.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include "Box.hpp"

int main()
{
    const Box box1 {2.0, 3.0, 4.0};                                 // An arbitrary box
    Box box2 {5.0};                                                 // A box that is a cube
    
    std::cout << "box1 volume = " << box1.volume() << std::endl;
    std::cout << "box2 volume = " << box2.volume() << std::endl;

    Box box3 {box2};
    std::cout << "box3 volume = " << box3.volume() << std::endl;    // Volume = 125

    std::cout << std::endl;

    Box boxes[6] {box1, box2, box3, Box {2.0}};
}
