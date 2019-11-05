// Name: ToughPack.hpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko)
// Date: 11/05/2019-12:48:09
// Description: Defines the ToughPack class

#ifndef TOUGHPACK_HPP
#define TOUGHPACK_HPP

#include "Box.hpp"

class ToughPack : public Box
{
public:
	// Constructor
	ToughPack(double lv, double wv, double hv) : Box {lv, wv, hv} {}

	// Function to calculate the volume of a Tough Pack allowing 15% for packing
	double volume() const { return 0.85 * length * width * height; }
};

#endif
