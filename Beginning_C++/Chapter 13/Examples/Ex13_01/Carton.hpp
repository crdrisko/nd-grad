// Name: Carton.hpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko)
// Date: 10/31/2019-14:24:28
// Description: Defines the Carton class with the Box class as base

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
	explicit Carton(std::string_view mat = "Cardboard") : material {mat} {} 		// Constructor
};

#endif
