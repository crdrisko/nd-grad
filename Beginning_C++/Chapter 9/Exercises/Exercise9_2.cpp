/***********************************************************************\ 
|* Name: Exercise9_2.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Date: 06/06/19-12:58:53                                             *|
|* Description: Explaining the error between initializing the strings  *|
|*  this way and how we did in Ex9_01.cpp                              *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise9_2.cpp -o Exercise9_2.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <string_view>

template <typename T> 
T larger(T a, T b);                                 // Function template prototype

template <>
const char* larger(const char* a, const char* b);   // Function template specialization prototype

int main()
{
    std::cout << "Larger of 1.5 and 2.5 is " << larger(1.5, 2.5) << std::endl;
    std::cout << "Larger of 3.5 and 4.5 is " << larger(3.5, 4.5) << std::endl;

    int big_int {17011983}, small_int {10};
    std::cout << "Larger of " << big_int << " and " << small_int << " is " 
              << larger(big_int, small_int) << std::endl;
    
    // Problem Piece
    const auto z_string = "Z", a_string = "A";
    std::cout << "Larger of " << a_string << " and " << z_string 
              << " is " << larger(a_string, z_string) << std::endl;
}

// Template for functions to return the larger of two values
template <typename T> T larger(T a, T b)
{
    return a > b ? a : b;
}

template <>
const char* larger(const char* a, const char* b)
{
    return std::string_view{a} > std::string_view{b} ? a : b;
}