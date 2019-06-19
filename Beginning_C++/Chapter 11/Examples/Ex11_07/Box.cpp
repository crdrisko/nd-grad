// Name: Box.cpp
// Author: crdrisko
// Date: 06/18/2019-09:26:27
// Description: For use with Ex11_07.cpp

#include <iostream>
#include "Box.hpp"

// Constructor definintion
Box::Box(double lv, double wv, double hv) : _length{lv}, _width{wv}, _height{hv} {}

// Function to calculate the volume of a box
double Box::volume() const
{
    return _length * _width * _height;
}