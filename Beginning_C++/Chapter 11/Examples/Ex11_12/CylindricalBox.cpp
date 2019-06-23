// Name: CylindricalBox.cpp
// Author: Cody R. Drisko (crdrisko) 
// Date: 06/23/2019-15:32:02
// Description: For use with Ex11_12.cpp

#include "CylindricalBox.hpp"

CylindricalBox::CylindricalBox(float r, float h, std::string_view mat)
    : radius (r), height (h), material (mat) {}

double CylindricalBox::volume() const
{
    return PI * radius * radius * height;
}
