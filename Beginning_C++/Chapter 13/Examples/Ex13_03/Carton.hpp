// Name: Carton.hpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko)
// Date: 11/04/2019-14:47:56
// Description: Defines the Carton class with the Box class as base

#ifndef CARTON_HPP
#define CARTON_HPP

#include <string>
#include <string_view>
#include "Box.hpp"

class Carton : public Box
{
private:
	std::string material {"Cardboard"};

public:
	Carton(double lv, double wv, double hv, std::string_view mat)
		: Box {lv, wv, hv}, material {mat}
	{
		std::cout << "Carton(double, double, double, string_view) called.\n";
	}

	explicit Carton(std::string_view mat) : material {mat}
	{
		std::cout << "Carton(string_view) called.\n";
	}

	Carton(double side, std::string_view mat) : Box {side}, material {mat}
	{
		std::cout << "Carton(duble, string_view) called.\n";
	}

	Carton() { std::cout << "Carton() called.\n"; }

	// Copy Constructor
	Carton(const Carton& carton) : Box {carton}, material {carton.material}
	{
		std::cout << "Carton copy constructor." << std::endl;
	}
};

#endif
