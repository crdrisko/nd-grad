// Name: Box.hpp
// Author: crdrisko
// Date: 06/13/2019-12:46:57
// Description: For use with Ex11_01B.cpp

#ifndef BOX_HPP
#define BOX_HPP

class Box
{
private:
    double length {1.0};
    double width {1.0};
    double height {1.0};

public:
    // Constructors
    Box(double lengthValue, double widthValue, double heightValue);
    Box() = default;

    double volume();                    // Function to calculate the volume of a box
};

#endif

