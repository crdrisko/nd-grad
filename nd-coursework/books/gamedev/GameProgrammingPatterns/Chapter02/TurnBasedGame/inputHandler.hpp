// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: inputHandler.hpp
// Author: crdrisko
// Date: 07/27/2022-09:57:25
// Description:

#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "command.hpp"

enum INPUTBUTTONS
{
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT
};

bool isPressed(INPUTBUTTONS button);

class InputHandler
{
public:
    Command* handleInput();
};

#endif
