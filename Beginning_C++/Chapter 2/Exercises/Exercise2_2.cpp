/***********************************************************************\ 
|* Name: Exercise2_2.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Increased precision for the area of the cicle.         *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise2_2.cpp -o Exercise2_2.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    double radius {};
    const double pi {3.141592653589793238};
    double area {};
    unsigned int precision {};

    std::cout << "Enter the radius of a circle: ";
    std::cin  >> radius;
    std::cout << "Enter the number of decimal places: ";
    std::cin  >> precision;

    area = pi * radius * radius;

    std::cout << "The area of a circle with radius " 
              << std::fixed << std::setprecision(precision)
              << radius << " is " << area << "." << std::endl;
}