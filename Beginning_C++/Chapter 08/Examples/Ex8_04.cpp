/*************************************************************\ 
|* Name: Ex8_04.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 05/21/19-13:19:38                                   *|
|* Description: Modifying the value of a caller variable     *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex8_04.cpp -o Ex8_04.out -std=c++17 *|
\*************************************************************/

#include <iostream>

double changeIt(double* pointer_to_it);                 // Function prototype

int main()
{
    double it {5.0};
    double result {changeIt(&it)};                      // Now we pass the address

    std::cout << "After function execution, it = " << it
              << "\nResult returned is " << result << std::endl;
}

// Function to modify an argument and return it 
double changeIt(double* pit)
{
    *pit += 10.0;                                       // This modifies the copy
    std::cout << "Within function, *pit = " << *pit << std::endl;
    return *pit;
}
