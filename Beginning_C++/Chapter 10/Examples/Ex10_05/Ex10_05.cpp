/*************************************************************************\ 
|* Name: Ex10_05.cpp                                                     *|
|* Author: crdrisko                                                      *|
|* Date: 06/11/19-10:57:53                                               *|
|* Description: Creating and including your own header files             *|
|*                                                                       *|
|*                                                                       *|
|* Complile Command: g++ Ex10_05.cpp Power.cpp -o Ex10_05.out -std=c++17 *|
\*************************************************************************/

#include <iostream>
#include <iomanip>
#include "Power.hpp"                    // Contains the prototype for the power() function

int main()
{
    for (int i {-3}; i <= 3; ++i)       // Calculate powers of 8 from -3 to +3
        std::cout << std::setw(10) << power(8.0, i);
    
    std::cout << std::endl;
}
