/*************************************************************\ 
|* Name: Ex5_02.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Obtaining the number of array elements       *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex5_02.cpp -o Ex5_02.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <array>

int main()
{
    int values[] {2,3,5,7,11,13,17,19,23,29};

    std::cout << "There are " << sizeof(values) / sizeof(values[0]) 
              << " elements in the array." << std::endl;

    int sum {};
    for (size_t i {}; i < std::size(values); ++i)
    {
        sum += values[i];
    }
    std::cout << "The sum of the array elements is " << sum << std::endl;
}