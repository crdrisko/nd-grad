// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: vartmplauto1.cpp
// Author: crdrisko
// Date: 10/31/2020-15:25:04
// Description: Main program for modifying the global array object and printing its elements

#include "vartmplauto.hpp"

int main()
{
    arr<int, 5>[0]  = 17;
    arr<int, 5>[3]  = 42;
    arr<int, 5u>[1] = 11;
    arr<int, 5u>[3] = 33;
    printArr();
}
