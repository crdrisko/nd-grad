/***********************************************************************\ 
|* Name: Exercise3_1.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Takes an input integer and prints the integer, the     *|
|*  inverse, and the inverse + 1 in hexadecimal and decimal form.      *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise3_1.cpp -o Exercise3_1.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <iomanip>

int main()
{
    int input {};
    std::cout << "Enter an integer: ";
    std::cin  >> input;

    unsigned int hex_digits {2 * sizeof(int)};
    unsigned int hex_value_width {hex_digits + 2};

    std::cout << "   Integer" 
              << "\t   ~Integer" 
              << "\t ~Integer+1 " << std::endl; 
    
    std::cout << std::hex << std::showbase << std::internal << std::setfill('0')
              << std::setw(hex_value_width) << input
              << "\t " << std::setw(hex_value_width) << ~input 
              << "\t " << std::setw(hex_value_width) << ~input + 1 << std::endl;

    std::cout << std::dec
              << "\t" << input 
              << "\t\t" << ~input 
              << "\t\t" << ~input + 1 << std::endl; 

}