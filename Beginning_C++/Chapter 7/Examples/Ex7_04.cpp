/*************************************************************\ 
|* Name: Ex7_04.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Searching within strings                     *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex7_04.cpp -o Ex7_04.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <string>

int main()
{
    std::string sentence {"Manners maketh man"};
    std::string word {"man"};
    std::cout << sentence.find(word) << std::endl;      // Outputs 15
    std::cout << sentence.find("Ma") << std::endl;      // Outputs 0
    std::cout << sentence.find('k') << std::endl;       // Outputs 10
    std::cout << sentence.find('x') << std::endl;       // Outputs std::string::npos
}