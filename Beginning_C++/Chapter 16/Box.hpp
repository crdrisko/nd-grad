// Name: Box.hpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko)
// Date: 12/17/2019-13:20:37
// Description: Using a class template

#ifndef BOX_HPP
#define BOX_HPP

class Box
{
private:
    double length {1.0};
    double width  {1.0};
    double height {1.0};

public:
    Box(double lv, double wv, double hv) : length{lv}, width{wv}, height{hv} {}
    Box() = default;

    double volume() const { return length * width * height; }
};

#endif
