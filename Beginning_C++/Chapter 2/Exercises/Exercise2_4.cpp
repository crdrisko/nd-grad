/***********************************************************************\ 
|* Name: Exercise2_4.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Calculating the height of a tree given the angle,      *|
|*  distance from the tree, and your height above the ground.          *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise2_4.cpp -o Exercise2_4.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    double height_of_tree {};                    // Measured in feet
    double height_of_eye {};                     // Measured in inches 
    double d_feet {};                            // Measured in feet
    double d_inches {};                          // Measured in inches
    double angle {};                             // Measured in degrees
    
    const double pi {3.141592653589793238};
    const double inches_per_foot {12.0};

    // Distance to the tree
    std::cout << "Enter the distance, d, you are away from the tree in feet and inches: ";
    std::cin  >> d_feet >> d_inches;
    const double distance_to_tree {d_feet + d_inches / inches_per_foot};

    // Height of your eye
    std::cout << "Enter the height of your eye in inches: ";
    std::cin  >> height_of_eye;
    height_of_eye /= inches_per_foot;

    // Angle 
    std::cout << "Enter the angle in degrees: ";
    std::cin  >> angle;
    angle *= pi / 180.0;                         // Convert to radians


    height_of_tree = height_of_eye + distance_to_tree * std::tan(angle);
    const unsigned height_feet {static_cast<unsigned>(height_of_tree)};
    const unsigned height_inches {static_cast<unsigned>(std::round(inches_per_foot * (height_of_tree - height_feet)))};


    std::cout << "The height of the tree is " << height_feet << "\' " 
              << height_inches << "\"." << std::endl;
}