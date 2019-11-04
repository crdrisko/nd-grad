// Name: Box.hpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko)
// Date: 10/31/2019-14:24:21
// Description: Defines the Box class

#ifndef BOX_HPP
#define BOX_HPP

#include <iostream>				// For standard streams
#include <iomanip>				// For stream manipulators

class Box
{
private:
	double length {1.0};
	double width  {1.0};
	double height {1.0};

public:
	// Constructors
	Box(double lv, double wv, double hv) : length {lv}, width {wv}, height {hv} {}
	Box() = default;			// No-arg constructor

	double volume() const { return length * width * height; }

	// Accessors 
	double getLength() const { return length; }
	double getWidth()  const { return width;  }
	double getHeight() const { return height; }
};

// Stream output for Box objects
inline std::ostream& operator<<(std::ostream& stream, const Box& box)
{
	stream << " Box(" << std::setw(2) << box.getLength() << ','
					  << std::setw(2) << box.getWidth()  << ','
					  << std::setw(2) << box.getHeight() << ')';
	return stream;
}

#endif
