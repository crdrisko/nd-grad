/***********************************************************************\ 
|* Name: Exercise5_1.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: A program that outputs the square of odd integers from *|
|*  1 to an end value specified by the user.                           *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise5_1.cpp -o Exercise5_1.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <vector>

int main()
{
    long limit {};
    std::cout << "Enter an integer to be the upper limit: "; 
    std::cin  >> limit;

    std::vector<long> vec(limit+1, 0L);
    for (size_t i {}; i < limit; ++i)
    {
        if (i%2)
            continue;
        else
            vec[i] = (i + 1) * (i + 1);
            std::cout << vec[i] << std::endl;
    }
}