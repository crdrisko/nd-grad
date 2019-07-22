/*************************************************************\ 
|* Name: Ex2_01.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Writing values of variables to cout          *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex2_01.cpp -o Ex2_01.out -std=c++17 *|
\*************************************************************/

#include <iostream>

int main()
{
    int apple_count {15};                                                // Number of apples
    int orange_count {5};                                                // Number of oranges
    int total_fruit {apple_count + orange_count};                        // Total number of fruit

    std::cout << "The value of apple_count is " << apple_count << std::endl;
    std::cout << "The value of orange_count is " << orange_count << std::endl;
    std::cout << "The value of total_fruit is " << total_fruit << std::endl;
    return 0;
}