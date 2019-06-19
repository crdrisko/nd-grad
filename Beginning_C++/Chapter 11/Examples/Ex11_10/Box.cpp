// Name: Box.cpp
// Author: crdrisko
// Date: 06/18/2019-13:15:50
// Description: For use with Ex11_10.cpp

#include <iostream>
#include "Box.hpp"

Box::Box(double lv, double wv, double hv) : length {lv}, width {wv}, height {hv}        // Constructor definition 
{
    std::cout << "Box constructor 1 called." << std::endl;
}

Box::Box(double side) : Box{side, side, side}                                           // Consructor for a cube
{
    std::cout << "Box constructor 2 called." << std::endl;
}

Box::Box()                                                                              // Default constructor
{
    std::cout << "Default Box constructor called." << std::endl;
}

Box::Box(const Box& box) : length {box.length}, width {box.width}, height {box.height}  // Copy constructor
{
    std::cout << "Box copy constructor called." << std::endl;
}

// Function to calculate the volume of a box
double Box::volume() const
{
    return length * width * height;
}
