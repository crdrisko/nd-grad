// Name: Ex13_02.cpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko) 
// Date: 11/04/2019-12:05:01
// Description: Calling base class constructors in a derived class constructor

#include <iostream>
#include "Carton.hpp"				// For the Carton Class

int main()
{
    // Create four Carton objects
	Carton carton1;								std::cout << std::endl;
	Carton carton2 {"Thin Cardboard"};			std::cout << std::endl;
	Carton carton3 {4.0, 5.0, 6.0, "Plastic"};	std::cout << std::endl;
	Carton carton4 {2.0, "Paper"};				std::cout << std::endl;

	std::cout << "carton1 volume is " << carton1.volume() << std::endl;
	std::cout << "carton2 volume is " << carton2.volume() << std::endl;
	std::cout << "carton3 volume is " << carton3.volume() << std::endl;
	std::cout << "carton4 volume is " << carton4.volume() << std::endl;	
}
