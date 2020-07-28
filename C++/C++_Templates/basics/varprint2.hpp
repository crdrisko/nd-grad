// Name: varprint2.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/27/2020-10:39:28
// Description: Printing a variable number of arguments where the templates differ only by a training parameter pack

#ifndef VARPRINT2_HPP
#define VARPRINT2_HPP

#include <iostream>

template <typename T>
void print(T arg)
{
    std::cout << arg << '\n';                               // print passed argument
}

template <typename T, typename... Types>
void print(T firstArg, Types... args)
{
    print(firstArg);                                        // print first argument
    print(args...);                                         // call print() for remaining arguments
}

#endif
