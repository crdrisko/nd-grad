// Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: main.cpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description:

#include <cstddef>
#include <iostream>

#include <engine2d/engine.hpp>

#include "npgBuilder/scenes/npgScene.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <config_file>\n";
        return EXIT_FAILURE;
    }

    Engine2D::Engine engine {argv[1]};

    // Set the default scene ourself so the engine doesn't need to know about it
    engine.setDefaultScene<NPGBuilder::NPGScene>("NPGBuilder", argv[1]);
    engine.run();
}
