// Name: Box.cpp
// Author: crdrisko
// Date: 06/18/2019-12:52:32
// Description: For use with Ex11_09.cpp

#include <iostream>
#include "Box.hpp"

// Constructor definition
Box::Box(double lv, double wv, double hv) : length {lv}, width {wv}, height {hv}
{
    std::cout << "Box constructor called." << std::endl;
}

// Function to calculate the volume of a box
double Box::volume() const
{
    return length * width * height;
}
