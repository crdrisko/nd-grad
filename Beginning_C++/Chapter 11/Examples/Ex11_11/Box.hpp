// Name: Box.hpp
// Author: Cody R. Drisko (crdrisko)
// Date: 06/23/2019-14:48:53
// Description: For use with Ex11_11.cpp

#ifndef BOX_HPP
#define BOX_HPP
#include <iostream>

class Box
{
private:
    double length {1.0};
    double width  {1.0};
    double height {1.0};
    static inline size_t objectCount {};            // Count of objects in existence

public:
    // Constructors
    Box(double lv, double wv, double hv);
    Box(double side);                               // Constructor for a cube
    Box();                                          // Default constructor
    Box(const Box& box);                            // Copy constructor

    double volume() const;                          // Function to calculate the volume of a box

    size_t getObjectCount() const { return objectCount; }
};

#endif

