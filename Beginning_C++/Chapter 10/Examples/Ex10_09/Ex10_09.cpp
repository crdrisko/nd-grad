/***************************************************************\ 
|* Name: Ex10_09.cpp                                           *|
|* Author: crdrisko                                            *|
|* Date: 06/12/2019-12:44:15                                   *|
|* Description: Demonstrating assertions                       *|
|*                                                             *|
|*                                                             *|
|* Complile Command: g++ Ex10_09.cpp -o Ex10_09.out -std=c++17 *|
\***************************************************************/

#include <iostream>
#include <cassert>

int main()
{
    int y {5};

    for (int x {}; x < 20; ++x)
    {
        std::cout << "x = " << x << " y = " << y << std::endl;
        assert(x < y);
    }
}
