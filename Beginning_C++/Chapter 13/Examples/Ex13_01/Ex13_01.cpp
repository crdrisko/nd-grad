// Name: Ex13_01.cpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko) 
// Date: 10/31/2019-14:24:14
// Description: Defining and using a class

#include <iostream>
#include "Box.hpp"
#include "Carton.hpp"

int main()
{
    // Create a Box object and two Carton objects
	Box box {40.0, 30.0, 20.0};
	Carton carton;
	Carton chocolateCarton {"Solid bleached paperboard"};
	
	// Check them out - sizes first of all
	std::cout << "box occupies " << sizeof box << " bytes" << std::endl;
	std::cout << "carton occupies " << sizeof carton << " bytes" << std::endl;
	std::cout << "chocolateCarton occupies " << sizeof chocolateCarton << " bytes" << std::endl;

	// Now volumes...
	std::cout << "box volume is " << box.volume() << std::endl;
	std::cout << "carton volume is " << carton.volume() << std::endl;
	std::cout << "chocolateCarton volume is " << chocolateCarton.volume() << std::endl;

	std::cout << "chocolateCarton length is " << chocolateCarton.getLength() << std::endl;

	// Uncomment any of the following for an error...
	// box.length = 10.0;
	// chocolateCarton.length = 10.0;
}
