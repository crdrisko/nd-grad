/*************************************************************\ 
|* Name: Ex9_03.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 06/06/19-11:06:03                                   *|
|* Description: Using return type deduction with templates   *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex9_03.cpp -o Ex9_03.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <string>

// Template for functions to return the larger of two values
// Supports implicit conversion of differently-typed arguments
template <typename T1, typename T2> 
auto larger(T1 a, T2 b)
{
    return a > b ? a : b;
}

int main()
{
    int small_int {10};
    std::cout << "Larger of " << small_int << " and 9.6 is "
              << larger(small_int, 9.6) << std::endl;

    std::string a_string {"A"};
    std::cout << "Larger of \"" << a_string << "\" and \"Z\" is "
              << '"' << larger(a_string, "Z") << '"' << std::endl;
}
