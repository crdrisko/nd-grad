// Name: Ex14_02.cpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko) 
// Date: 11/05/2019-12:48:18
// Description:

#include <iostream>
#include "Box.hpp"									// For the Box class
#include "ToughPack.hpp"							// For the ToughPack class
#include "Carton.hpp"								// For the Carton class

int main()
{
    Box box {20.0, 30.0, 40.0};
	ToughPack hardcase {20.0, 30.0, 40.0}; 			// A derived box - same size
	Carton carton {20.0, 30.0, 40.0, "plastic"};	// A different derived box

	box.showVolume();								// Volume of Box
	hardcase.showVolume();							// Volume of ToughPack
	carton.showVolume();							// Volume of Carton

	// Now using a base pointer...
	Box* pBox {&box};								// Points to type Box
	std::cout << "\nbox volume through pBox is " << pBox->volume() << std::endl;
	pBox->showVolume();

	pBox = &hardcase;								// Points to type ToughPack
	std::cout << "hardcase volume through pBox is " << pBox->volume() << std::endl;
	pBox->showVolume();

	pBox = &carton;									// Points to type Carton
	std::cout << "carton volume through pBox is " << pBox->volume() << std::endl;
	pBox->showVolume();
}
