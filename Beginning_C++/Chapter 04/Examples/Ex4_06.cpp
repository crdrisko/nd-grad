/*************************************************************\ 
|* Name: Ex4_06.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Using the conditional operator to select     *|
|*  output                                                   *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex4_06.cpp -o Ex4_06.out -std=c++17 *|
\*************************************************************/

#include <iostream>

int main()
{
    int mice {};
    int brown {};
    int white {};

    std::cout << "How many brown mice do you have? ";
    std::cin  >> brown;
    std::cout << "How many white mice do you have? ";
    std::cin  >> white;

    mice = brown + white;

    std::cout << "You have " << mice 
              << (mice == 1? " mouse" : " mice")
              << " in total." << std::endl;
}