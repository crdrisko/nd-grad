/*************************************************************\ 
|* Name: Ex9_05.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 06/06/19-12:45:46                                   *|
|* Description: Defining templates for functions that accept *|
|*  fixed-size arrays                                        *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex9_05.cpp -o Ex9_05.out -std=c++17 *|
\*************************************************************/

#include <iostream>

template <typename T, size_t N>
T average(const T (&array)[N]);

int main()
{
    double doubles[2] { 1.0, 2.0 };
    std::cout << average(doubles) << std::endl;

    double moreDoubles[] { 1.0, 2.0, 3.0, 4.0 };
    std::cout << average(moreDoubles) << std::endl;

    // double* pointer = doubles;
    // std::cout << average(pointer) << std::endl;  /* will not compile */

    std::cout << average( {1.0, 2.0, 3.0, 4.0} ) << std::endl;

    int ints[] = { 1, 2, 3, 4 };
    std::cout << average(ints) << std::endl;
}

template <typename T, size_t N>
T average(const T (&array)[N])
{
    T sum {};                                       // Accumulate total in here
    for (size_t i {}; i < N; ++i)
        sum += array[i];                            // Sum array elements
    return sum / N;                                 // Return average
}