// Name: Box.hpp
// Author: crdrisko
// Date: 06/13/2019-15:29:33
// Description: For use with Ex11_03.cpp

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
    Box(double lv, double wv, double hv);
    explicit Box(double side);                  // Constructor for a cube
    Box() = default;                            // No-arg constructor

    double volume();                            // Function to calculate the volume of a box
};

#endif

