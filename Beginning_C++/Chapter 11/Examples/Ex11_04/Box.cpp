// Name: Box.cpp
// Author: crdrisko
// Date: 06/15/2019-16:28:59
// Description: For use with Ex11_04.cpp

#include <iostream>
#include "Box.hpp"

// Constructor definition
Box::Box(double lv, double wv, double hv) : length{lv}, width{wv}, height{hv} {}

// Function to calculate the volume of a box
double Box::volume()
{
    return length * width * height;
}
