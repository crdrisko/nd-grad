// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: inputHandler.cpp
// Author: crdrisko
// Date: 07/27/2022-09:57:37
// Description:

#include "inputHandler.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "command.hpp"

Command* InputHandler::handleInput()
{
    if (isPressed(BUTTON_X))
        return buttonX_;
    if (isPressed(BUTTON_Y))
        return buttonY_;
    if (isPressed(BUTTON_A))
        return buttonA_;
    if (isPressed(BUTTON_B))
        return buttonB_;

    return nullptr;
}
