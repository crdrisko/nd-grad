// Name: Box.cpp
// Author: crdrisko
// Date: 06/13/2019-15:29:39
// Description: For use with Ex11_03.cpp

#include <iostream>
#include "Box.hpp"

// Constructor definition
Box::Box(double lv, double wv, double hv) : length{lv}, width{wv}, height{hv}
{
    std::cout << "Box constructor 1 called." << std::endl;
}

// Constructor for Box that is a cube
Box::Box(double side) : Box{side, side, side}
{
    std::cout << "Box constructor 2 called." << std::endl;
}

// Function to calculate the volume of a box
double Box::volume()
{
    return length * width * height;
}
