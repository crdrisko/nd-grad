// Name: Carton.hpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko)
// Date: 11/05/2019-12:47:50
// Description: Defines the Carton class

#ifndef CARTON_HPP
#define CARTON_HPP

#include <string>
#include <string_view>
#include "Box.hpp"

class Carton : public Box
{
private:
	std::string material;

public:
	// Constructor explicitly calling the base constructor
	Carton(double lv, double wv, double hv, std::string_view str="cardboard")
		: Box {lv, wv, hv}, material {str} {}
	
	// Function to calculate the volume of a Carton object
	double volume() const
	{
		const double vol { (length - 0.5) * (width - 0.5) * (height - 0.5) };
		return vol > 0.0? vol : 0.0;
	}
};

#endif
