// Name: Ex14_01.cpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko) 
// Date: 11/05/2019-12:04:14
// Description: Behavior of inherited functions in a derived class

#include "Box.hpp"									// For the Box class
#include "ToughPack.hpp"							// For the ToughPack class

int main()
{
    Box box {20.0, 30.0, 40.0};						// Define a box
	ToughPack hardcase {20.0, 30.0, 40.0};			// Declare tough box - same size

	box.showVolume();								// Display volume of base box
	hardcase.showVolume();							// Display volume of derived box

	std::cout << "hardcase volume is " << hardcase.volume() << std::endl;
	Box *pBox {&hardcase};
	std::cout << "hardcase volume through pBox is " << pBox->volume() << std::endl;
}
