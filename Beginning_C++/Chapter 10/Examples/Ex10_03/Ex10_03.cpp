/*************************************************************************\ 
|* Name: Ex10_03.cpp                                                     *|
|* Author: crdrisko                                                      *|
|* Date: 06/10/19-15:30:52                                               *|
|* Description: Creating functions with internal linkage                 *|
|*                                                                       *|
|*                                                                       *|
|* Complile Command: g++ Ex10_03.cpp Power.cpp -o Ex10_03.out -std=c++17 *|
\*************************************************************************/

#include <iostream>
#include <iomanip>

double power(double x, int n);
// double compute(double, unsigned n);

int main()
{
    for (int i {-3}; i <= 3; ++i)       // Calculate powers of 8 from -3 to +3
        std::cout << std::setw(10) << power(8.0, i);

    // unsigned exponent = 8;
    // std::cout << compute(2.0, exponent) << std::endl;

    std::cout << std::endl;
}
