/*************************************************************\ 
|* Name: Ex8_05.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 05/21/19-13:19:46                                   *|
|* Description: Passing an array to a function               *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex8_05.cpp -o Ex8_05.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <array>                                        // For std::size()

double average(double array[], size_t count);           // Function prototype

int main()
{
    double values[] {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::cout << "Average = " << average(values, std::size(values)) << std::endl;
}

// Function to compute an average
double average(double array[], size_t count)
{
    double sum {};
    for (size_t i {}; i < count; ++i)
        sum += array[i];                                // Sum array elements
    return sum / count;                                 // Return average
}
