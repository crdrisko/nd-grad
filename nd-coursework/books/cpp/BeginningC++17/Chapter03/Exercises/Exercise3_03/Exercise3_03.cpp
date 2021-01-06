// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise3_03.cpp
// Author: cdrisko
// Date: 04/23/2020-14:32:21
// Description: Predict the output of the following code

#include <iostream>

int main()
{
    auto k {430u};
    auto j {(k >> 4) & ~(~0u << 3)};
    std::cout << j << std::endl;
}
