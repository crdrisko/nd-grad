/***********************************************************************\ 
|* Name: Exercise4_2.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Checking to see if two integers are multiples of       *|
|*  each other                                                         *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise4_2.cpp -o Exercise4_2.out -std=c++17 *|
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

    if ((first <= 0) || (second <= 0))
    {
        std::cout << "Sorry, you entered a number less than or equal to zero."
                  << std::endl;
    }
    else   
    {
        long result {};
        if (first > second)
        {
            result = first % second;
            if (!result)
            {
                std::cout << second << " is an exact multiple of " << first << "."
                          << std::endl;
            }
            else 
            {
                std::cout << second << " is not an exact multiple of " << first << "."
                          << std::endl;
            }
        }
        else if (first < second)
        {
            result = second % first;
            if (!result)
            {
                std::cout << first << " is an exact multiple of " << second << "."
                          << std::endl;
            }
            else 
            {
                std::cout << first << " is not an exact multiple of " << second << "."
                          << std::endl;
            }
        }
    }
}