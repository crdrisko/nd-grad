/***********************************************************************\ 
|* Name: Exercise3_3.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Demonstrates shifting operators and bit manipulation,  *|
|*  worked out in notebook.                                            *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise3_3.cpp -o Exercise3_3.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    auto k {430u};
    auto j {(k >> 4) & ~(~0u << 3)};
    std::cout << j <<std::endl;
}