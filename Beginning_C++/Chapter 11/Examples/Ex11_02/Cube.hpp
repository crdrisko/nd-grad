// Name: Cube.hpp
// Author: crdrisko
// Date: 06/13/2019-14:48:21
// Description: For use with Ex11_02.cpp

#ifndef CUBE_HPP
#define CUBE_HPP

class Cube
{
private:
    double side;

public:
    Cube(double aSide);                                 // Constructor
    double volume();                                    // Calculate volume of a cube
    bool hasLargerVolumeThan(Cube aCube);               // Compare volume of a cube with another
};

#endif

