// Name: Exercise2_02.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/23/2020-10:18:58
// Description: Compute the area of a circle to the desired precision

#include <iomanip>
#include <iostream>

int main()
{
    const double pi {3.141592653589793238};

    double radius {};
    std::cout << "Enter the radius of the circle: ";
    std::cin  >> radius;

    unsigned int precision {};
    std::cout << "Enter the number of digits for output precision: ";
    std::cin  >> precision;

    const double area = pi * radius * radius;

    std::cout << std::setprecision(precision)
              << "The area of the circle with a radius of " << radius << " is " << area << std::endl;
}
