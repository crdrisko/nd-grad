// Name: Box.cpp
// Author: crdrisko
// Date: 06/13/2019-12:46:51
// Description: For use with Ex11_01B.cpp

#include <iostream>
#include "Box.hpp"

// Constructor definition
Box::Box(double lengthValue, double widthValue, double heightValue)
{
    std::cout << "Box constructor called." << std::endl;
    length = lengthValue;
    width = widthValue;
    height = heightValue;
}

// Function to calculate the volume of a box
double Box::volume()
{
    return length * width * height;
}