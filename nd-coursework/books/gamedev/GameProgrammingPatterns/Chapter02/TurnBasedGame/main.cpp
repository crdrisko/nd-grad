// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: main.cpp
// Author: crdrisko
// Date: 07/27/2022-09:47:52
// Description:

#include "command.hpp"
#include "inputHandler.hpp"

int main()
{
    InputHandler inputHandler {};

    Command* command = inputHandler.handleInput();

    if (command)
    {
        command->execute();
        command->undo();

        delete command;
    }
}
