/***********************************************************************\ 
|* Name: Exercise2_1.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Program that will compute the area of a circle.        *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise2_1.cpp -o Exercise2_1.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    float radius {};
    const float pi {3.14159265};
    float area {};

    std::cout << "Enter the radius of a circle: ";
    std::cin  >> radius;

    area = pi * radius * radius;

    std::cout << "The area of a circle with radius " << radius << " is "
              << area << "." << std::endl;

}