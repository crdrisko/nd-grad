/***********************************************************************\ 
|* Name: Exercise2_3.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Converts a distance in inches to feet and inches.      *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise2_3.cpp -o Exercise2_3.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    const unsigned inches_per_foot {12};
    unsigned int inches {}, feet {};
    unsigned total_inches {};

    std::cout << "Enter the number of inches you want converted: ";
    std::cin  >> total_inches;

    feet = total_inches / inches_per_foot;
    inches = total_inches % inches_per_foot;

    std::cout << "The number of feet and inches in " << total_inches << "\" is " 
              << feet << "\' " << inches << "\"." << std::endl;
}