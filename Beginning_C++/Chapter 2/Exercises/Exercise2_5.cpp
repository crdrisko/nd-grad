/***********************************************************************\ 
|* Name: Exercise2_5.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Calclating BMI (kg/m^2) from height (ft, in) and       *|
|*  weight (lbs).                                                      *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise2_5.cpp -o Exercise2_5.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    double height_feet {};
    double height_inches {};
    double weight_lbs {};

    const double lbs_per_kg {2.2};
    const double meters_per_feet {0.3048};
    const double inches_per_feet {12.0};

    std::cout << "Enter your height in feet and inches: ";
    std::cin  >> height_feet >> height_inches;
    const double height_meters {(height_feet + height_inches / inches_per_feet) * meters_per_feet};

    std::cout << "Enter your weight in pounds: ";
    std::cin  >> weight_lbs;
    const double weight_kg {weight_lbs / lbs_per_kg};

    const double BMI {weight_kg / (height_meters * height_meters)};
    std::cout << "Your BMI in kg/m^2 is " << std::setprecision(4) << BMI << "." << std::endl;

}