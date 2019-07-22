/***********************************************************************\ 
|* Name: Exercise1_3.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: The following program produces several compiler        *|
|*  errors. Find these errors and corect them so the program can       *|
|*  complile cleanly and run.                                          *|
|*                                                                     *|
|* Complile Command: g++ Exercise1_3.cpp -o Exercise1_3.out -std=c++17 *|
\***********************************************************************/


#include <iostream>                           // include --> #include
                                              
int main()                                    // Int --> int
{                                             
    std::cout << "Hello World" << std::endl;  // std:cout --> std::cout and std:endl --> std::endl;
}                                             // ) --> }