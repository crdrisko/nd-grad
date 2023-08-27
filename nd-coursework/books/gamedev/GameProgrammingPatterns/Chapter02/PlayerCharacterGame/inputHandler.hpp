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
    BUTTON_X,
    BUTTON_Y,
    BUTTON_A,
    BUTTON_B,
};

bool isPressed(INPUTBUTTONS button);

class InputHandler
{
private:
    Command* buttonX_;
    Command* buttonY_;
    Command* buttonA_;
    Command* buttonB_;

public:
    Command* handleInput();
};

#endif
