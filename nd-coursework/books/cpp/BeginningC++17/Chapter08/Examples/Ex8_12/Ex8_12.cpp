// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_12.cpp
// Author: crdrisko
// Date: 08/14/2020-08:23:57
// Description: Program that lists its command line arguments

#include <iostream>

int main(int argc, char* argv[])
{
    for (int i {}; i < argc; ++i)
        std::cout << argv[i] << std::endl;
}
