// Name: Box.hpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko)
// Date: 11/05/2019-12:47:42
// Description: Defines the Box class

#ifndef BOX_HPP
#define BOX_HPP

#include <iostream>

class Box
{
protected:
	double length {1.0};
	double width  {1.0};
	double height {1.0};

public:
	Box() = default;
	Box(double lv, double wv, double hv) : length {lv}, width {wv}, height {hv} {}

	// Function to show the volume of an object
	void showVolume() const
	{
		std::cout << "Box usable volume is " << volume() << std::endl;
	}

	// Function to calculate the volume of a Box object
	virtual double volume() const { return length * width * height; }
};

#endif