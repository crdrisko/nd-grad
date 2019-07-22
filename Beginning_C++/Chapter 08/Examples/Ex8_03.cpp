/*************************************************************\ 
|* Name: Ex8_03.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 05/21/19-13:19:28                                   *|
|* Description: Failing to modify the original value of a    *|
|*  function argument                                        *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex8_03.cpp -o Ex8_03.out -std=c++17 *|
\*************************************************************/

#include <iostream>

double changeIt(double value_to_be_changed);            // Function prototype

int main()
{
    double it {5.0};
    double result {changeIt(it)};

    std::cout << "After function execution, it = " << it
              << "\nResult returned is " << result << std::endl;
}

// Function that attempts to modify an argument and return it 
double changeIt(double it)
{
    it += 10.0;                                         // This modifies the copy
    std::cout << "Within function, it = " << it << std::endl;
    return it;
}
