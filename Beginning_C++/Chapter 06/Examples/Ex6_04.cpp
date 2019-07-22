/*************************************************************\ 
|* Name: Ex6_04.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Using an array of pointers                   *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex6_04.cpp -o Ex6_04.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <array>                                // for std::size()

int main()
{
    const char* pstars[] {
                            "Fatty Arbuckle", "Clara Bow",
                            "Lassie", "Slim Pickens",
                            "Boris Karloff", "Mae West",
                            "Oliver Hardy", "Greta Garbo"
                         };
    std::cout << "Pick a lucky star! Enter a number between 1 and "
              << std::size(pstars) << ": ";
    size_t choice {};
    std::cin  >> choice;
    if (choice >= 1 && choice <= std::size(pstars))
    {
        std::cout << "Your lucky star is " << pstars[choice - 1] << std::endl;
    }
    else
    {
        std::cout << "Sorry, you haven't got a lucky star." << std::endl;
    }
}