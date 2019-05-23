/*************************************************************\ 
|* Name: Ex5_12.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Allocating an array at runtime               *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex5_12.cpp -o Ex5_12.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <iomanip>

int main()
{
    size_t count {};
    std::cout << "How many heights will you enter? ";
    std::cin  >> count;
    int height [count];                                 // Create the array of count elements

    // Read the heights
    size_t entered {};
    while (entered < count)
    {
        std::cout << "Enter a height: ";
        std::cin  >> height[entered];
        if (height[entered] > 0)
        {
            ++entered;
        }
        else
        {
            std::cout << "A height must be positive - try again.\n";
        }
    }

    // Calculate the sum of the heights
    unsigned int total {};
    for (size_t i {}; i < count; ++i)
    {
        total += height[i];
    }
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "The average height is " << static_cast<int>(total) / count << std::endl;
}