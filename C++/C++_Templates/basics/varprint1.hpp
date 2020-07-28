// Name: varprint1.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/27/2020-10:21:12
// Description: Printing a variable number of arguments

#ifndef VARPRINT1_HPP
#define VARPRINT1_HPP

#include <iostream>

void print()
{
}

template <typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << firstArg << '\n';                          // print first argument
    print(args...);                                         // call print() for remaining arguments
}

#endif
