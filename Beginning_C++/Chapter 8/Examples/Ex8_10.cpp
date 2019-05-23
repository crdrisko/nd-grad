/*************************************************************\ 
|* Name: Ex8_10.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 05/21/19-13:20:57                                   *|
|* Description: Implicit conversions of reference parameters *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex8_10.cpp -o Ex8_10.out -std=c++17 *|
\*************************************************************/

#include <iostream>

void double_it(double& it)      { it *=2; }
void print_it(const double& it) { std::cout << it << std::endl; }

int main()
{
    double d {123};
    double_it(d);
    print_it(d);

    int i {456};
    // double_it(i);            /* Error, does not compile! */
    print_it(i);
}
