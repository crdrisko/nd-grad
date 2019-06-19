// Name: Box.hpp
// Author: crdrisko
// Date: 06/18/2019-12:52:37
// Description: For use with Ex11_09.cpp

#ifndef BOX_HPP
#define BOX_HPP

class Box
{
private:
    double length;
    double width;
    double height;

public:
    // Constructors
    Box(double lv = 1.0, double wv = 1.0, double hv = 1.0);

    double volume() const;                                  // Function to calculate the volume of a box

    friend double surfaceArea(const Box& aBox);             // Friend function for the surface area
};

#endif

