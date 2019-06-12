/***************************************************************************\ 
|* Name: Ex10_07.cpp                                                       *|
|* Author: crdrisko                                                        *|
|* Date: 06/11/19-11:49:58                                                 *|
|* Description: Using functions in a namespace                             *|
|*                                                                         *|
|*                                                                         *|
|* Complile Command: g++ Ex10_07.cpp compare.cpp -o Ex10_07.out -std=c++17 *|
\***************************************************************************/

#include <iostream>
#include <vector>
#include "compare.hpp"

using compare::max;                 // using declaration for max

int main()
{
    using compare::min;             // using declaration for min

    std::vector<double> data {1.5, 4.6, 3.1, 1.1, 3.8, 2.1};
    std::cout << "Minimum double is " << min(data) << std::endl;
    std::cout << "Maximum double is " << max(data) << std::endl;
}
