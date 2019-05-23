/*************************************************************\ 
|* Name: Ex8_02.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 05/21/19-11:13:50                                   *|
|* Description: Calculating powers - rearranged              *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex8_02.cpp -o Ex8_02.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <iomanip>

double power(double, int);                    // Fails to compile without this function prototype
int main()
{  
    // Calculates powers of 8 from -3 to +3
    for (int i {-3}; i <= 3; ++i)
        std::cout << std::setw(10) << power(8.0, i);
        
    std::cout << std::endl;
}

// Function to calculate x to the power n
double power(double x, int n)
{
    double result {1.0};
    if (n >= 0)
    {
        for (int i {1}; i <= n; ++i)
            result *= x;
    }
    else
    {
        for (int i {1}; i <= -n; ++i)
            result /= x;
    }
    return result;
}
