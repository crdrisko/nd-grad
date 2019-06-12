/*************************************************************************\ 
|* Name: Ex10_01.cpp                                                     *|
|* Author: crdrisko                                                      *|
|* Date: 06/10/19-13:07:03                                               *|
|* Description: Calling external functions                               *|
|*                                                                       *|
|*                                                                       *|
|* Complile Command: g++ Ex10_01.cpp Power.cpp -o Ex10_01.out -std=c++17 *|
\*************************************************************************/

#include <iostream>
#include <iomanip>

double power(double x, int n);                  // Declaration of an external power() function

int main()
{
    for (int i {-3}; i <= 3; ++i)               // Calcualte powers of 8 from -3 to +3
        std::cout << std::setw(10) << power(8.0, i);
    
    std::cout << std::endl;
}
