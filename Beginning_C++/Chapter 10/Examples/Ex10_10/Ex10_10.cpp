/***************************************************************\ 
|* Name: Ex10_10.cpp                                           *|
|* Author: crdrisko                                            *|
|* Date: 06/12/2019-12:48:46                                   *|
|* Description: Using a static assertion                       *|
|*                                                             *|
|*                                                             *|
|* Complile Command: g++ Ex10_10.cpp -o Ex10_10.out -std=c++17 *|
\***************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include "average.hpp"

int main()
{
    std::vector<double> vectorData {1.5, 2.5, 3.5, 4.5};
    std::cout << "The average of vectorData is " << average(vectorData) << std::endl;

    // Uncomment the next lines for compiler errors...
    // std::vector<std::string> words {"this", "that", "them", "those"};
    // std::cout << "The average of words values is " << average(words) << std::endl;

    std::vector<float> emptyVector;
    average(emptyVector);               // Will trigger a runtime assertion!
}
