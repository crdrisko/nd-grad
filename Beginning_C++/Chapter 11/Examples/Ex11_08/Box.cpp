// Name: Box.cpp
// Author: crdrisko
// Date: 06/18/2019-09:58:19
// Description: For use with Ex11_08.cpp

#include <iostream>
#include "Box.hpp"

// Constructor definition
Box::Box(double lv, double wv, double hv) : length {lv}, width{wv}, height{hv} {}

// Function to calculate the volume of a box
double Box::volume() const
{
    return length * width * height;
}

// Function to print the volume of a Box to std::cout
void Box::printVolume() const
{
    // Count how many times printVolume() is called using a mutable member in a const function
    std::cout << "The volume of this box is " << volume() << std::endl;
    std::cout << "printVolume() has been called " << ++count << " time(s)" << std::endl; 
}
