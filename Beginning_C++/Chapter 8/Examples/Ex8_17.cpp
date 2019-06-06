/*************************************************************\ 
|* Name: Ex8_17.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 05/21/19-13:21:50                                   *|
|* Description: Recursive version of function for x to the   *|
|*  power n, n positive or negative                          *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex8_17.cpp -o Ex8_17.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <iomanip>

double power(double x, int n);

int main()
{
    for (int i {-3}; i <= 3; ++i)           // Calculate powers of 8 from -3 to +3
        std::cout << std::setw(10) << power( 8.0, i);

    std::cout << std::endl;
}

// Recursive function to calculate x to the power n
double power(double x, int n)
{
    if (n == 0)      return 1.0;
    else if (n > 0)  return x * power(x, n - 1);
    else /* n < 0 */ return 1.0 / power(x, -n);
}
