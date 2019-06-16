// Name: Box.cpp
// Author: crdrisko
// Date: 06/15/2019-17:10:18
// Description: For use with Ex11_05.cpp

#include <iostream>
#include "Box.hpp"

// Constructor definition
Box::Box(double lv, double wv, double hv) : length{lv}, width{wv}, height{hv} {}

// Function to calculate the volume of a box
double Box::volume()
{
    return length * width * height;
}

// Functions to access the dimensions of a box
Box& Box::setLength(double lv)
{
    if (lv > 0) length = lv;
    return *this;
}

Box& Box::setWidth(double wv)
{
    if (wv > 0) width = wv;
    return *this;
}

Box& Box::setHeight(double hv)
{
    if (hv > 0) height = hv;
    return *this;
}
