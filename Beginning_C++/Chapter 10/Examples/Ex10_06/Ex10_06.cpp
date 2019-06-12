/***************************************************************\ 
|* Name: Ex10_06.cpp                                           *|
|* Author: crdrisko                                            *|
|* Date: 06/11/19-11:41:34                                     *|
|* Description: Using a namespace                              *|
|*                                                             *|
|*                                                             *|
|* Complile Command: g++ Ex10_06.cpp -o Ex10_06.out -std=c++17 *|
\***************************************************************/

#include <iostream>
#include "Constants.hpp"

int main()
{
    std::cout << "pi has the value " << constants::pi << std::endl;
    std::cout << "This should be 2: " << constants::sqrt_2 * constants::sqrt_2 << std::endl;
}
