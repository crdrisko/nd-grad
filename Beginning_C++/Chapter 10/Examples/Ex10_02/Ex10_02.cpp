/***********************************************************************************\ 
|* Name: Ex10_02.cpp                                                               *|
|* Author: crdrisko                                                                *|
|* Date: 06/10/19-13:19:33                                                         *|
|* Description: Using an externally defined variable                               *|
|*                                                                                 *|
|*                                                                                 *|
|* Complile Command: g++ Ex10_02.cpp Power.cpp Range.cpp -o Ex10_02.out -std=c++17 *|
\***********************************************************************************/

#include <iostream>
#include <iomanip>

double power(double x, int n);          // Declaration of an external power() function
// int power_range;                     // Results in error
extern int power_range;                 // Declaration of an externally defined variable

int main()
{
    for (int i {-power_range}; i <= power_range; ++i)   // Calcualte powers of 8
        std::cout << std::setw(10) << power(8.0, i);
    
    std::cout << std::endl;
}
