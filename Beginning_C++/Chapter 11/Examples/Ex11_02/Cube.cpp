// Name: Cube.cpp
// Author: crdrisko
// Date: 06/13/2019-14:53:12
// Description: For use with Ex11_02.cpp

#include <iostream>
#include "Cube.hpp"

Cube::Cube(double aSide) : side{aSide} 
{
    std::cout << "Cube constructor called." << std::endl; 
}

double Cube::volume()
{
    return side * side * side;
}

bool Cube::hasLargerVolumeThan(Cube aCube)
{
    return volume() > aCube.volume();
}