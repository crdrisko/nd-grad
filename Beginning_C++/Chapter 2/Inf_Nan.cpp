/***************************************************************\ 
|* Name: Inf_Nan.cpp                                           *|
|* Author: crdrisko                                            *|
|* Description: To test how the compiler presents infinity     *|
|*  and NaN from calculations                                  *|
|*                                                             *|
|* Complile Command: g++ Inf_Nan.cpp -o Inf_Nan.out -std=c++17 *|
\***************************************************************/

#include <iostream>

int main()
{
    double a{ 1.5 }, b{}, c{};
    double result { a / b };
    std::cout << a << "/" << b << " = " << result << std::endl;
    std::cout << result << " + " << a << " = " << result + a << std::endl;
    result = b / c;
    std::cout << b << "/" << c << " = " << result << std::endl;
}