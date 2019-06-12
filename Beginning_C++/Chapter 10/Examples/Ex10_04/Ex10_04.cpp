/***************************************************************\ 
|* Name: Ex10_04.cpp                                           *|
|* Author: crdrisko                                            *|
|* Date: 06/10/19-15:42:47                                     *|
|* Description: Working with preprocessor operators            *|
|*                                                             *|
|*                                                             *|
|* Complile Command: g++ Ex10_04.cpp -o Ex10_04.out -std=c++17 *|
\***************************************************************/

#include <iostream>

#define DEFINE_PRINT_FUNCTION(NAME, COUNT, VALUE) \
    void NAME##COUNT() { std::cout << #VALUE << std::endl; }

DEFINE_PRINT_FUNCTION(fun, 123, Test 1 "2" 3)

int main()
{
    fun123();
}
