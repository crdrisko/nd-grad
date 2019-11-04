// Name: Ex13_03.cpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko) 
// Date: 11/04/2019-14:48:12
// Description: Using a derived class copy constructor

#include <iostream>
#include "Carton.hpp"						// For the Carton Class

int main()
{
    // Declare and initialize a Carton object
	Carton carton(20.0, 30.0, 40.0, "Glassine board");
	std::cout << std::endl;

	Carton cartonCopy(carton);				// Use copy constructor
	std::cout << std::endl;

	std::cout << "Volume of carton is " << carton.volume() << std::endl;
	std::cout << "Volume of cartonCopy is " << cartonCopy.volume() << std::endl;
}
