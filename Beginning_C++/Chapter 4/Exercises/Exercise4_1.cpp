/***********************************************************************\ 
|* Name: Exercise4_1.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Decides if two integers are equivalent                 *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise4_1.cpp -o Exercise4_1.out -std=c++17 *|
\***********************************************************************/

#include <iostream>

int main()
{
    long first {};
    long second {};
    
    std::cout << "Enter an integer: ";
    std::cin  >> first;
    std::cout << "Enter another integer: ";
    std::cin  >> second;

    if (first == second)
    {
        std::cout << "The two integers are equivalent.\n"
                  << "(" << first << " = " << second << ")" 
                  << std::endl;
    }
    else
    {
        std::cout << "These two integers are not equivalent.\n"
                  << "(" << first << " != " << second << ")" 
                  << std::endl;
    }
}