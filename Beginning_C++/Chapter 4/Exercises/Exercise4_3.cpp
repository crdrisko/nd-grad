/***********************************************************************\ 
|* Name: Exercise4_3.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Decides if a rounded double is between 1 and 50 or     *|
|*  50 and 100                                                         *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise4_3.cpp -o Exercise4_3.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    double number {};

    std::cout << "Enter a number: ";
    std::cin  >> number;

    long newNumber {};
    newNumber = std::lround(number);

    if ((newNumber > 1) && (newNumber < 100))
    {
        if (newNumber == 50)
        {
            std::cout << "The number you entered (" << number
                      << ") is (or rounds to) 50." 
                      << std::endl;
        }
        else 
        {
            if (newNumber < 50)
            {
                std::cout << "The number you entered (" << number
                          << ") is less than 50 but greater than 1." 
                          << std::endl;
            }
            else
            {
                std::cout << "The number you entered (" << number
                          << ") is greater than 50 but less than 100." 
                          << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Number you entered when rounded is out of bounds (1, 100)."
                  << std::endl;
    }
    




}