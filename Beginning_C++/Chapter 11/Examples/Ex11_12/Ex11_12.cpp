// Name: Ex11_12.cpp
// Author: Cody R. Drisko (crdrisko) 
// Date: 06/23/2019-15:31:38
// Description: Defining and accessing static constants

#include <iostream>
#include "CylindricalBox.hpp"

int main()
{
    const CylindricalBox bigBox { 1.23f, CylindricalBox::maxHeight, CylindricalBox::defaultMaterial };
    std::cout << "The volume of bigBox is " << bigBox.volume() << std::endl;
}
