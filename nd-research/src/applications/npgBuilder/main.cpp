// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: main.cpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description:

#include <iostream>

#include "npgBuilder/engine.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <config_file>\n";
        return EXIT_FAILURE;
    }

    Engine engine {argv[1]};
    engine.run();
}
