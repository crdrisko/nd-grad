// Name: Box.cpp
// Author: crdrisko
// Date: 06/16/2019-16:26:17
// Description: For use with Ex11_06.cpp


#include <iostream>
#include "Box.hpp"

// Constructor definition
Box::Box(double lv, double wv, double hv) : length{lv}, width{wv}, height{hv} {}

// Function to calculate the volume of a box
double Box::volume() const
{
    return length * width * height; 
}
