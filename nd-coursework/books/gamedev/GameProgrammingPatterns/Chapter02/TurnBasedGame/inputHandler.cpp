// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: inputHandler.cpp
// Author: crdrisko
// Date: 07/27/2022-09:57:37
// Description:

#include "inputHandler.hpp"

#include "command.hpp"

Command* InputHandler::handleInput()
{
    Unit* unit = getSelectedUnit();

    if (isPressed(BUTTON_UP))
    {
        // Move the unit up one
        int destY = unit->y() - 1;

        return new MoveUnitCommand(unit, unit->x(), destY);
    }

    if (isPressed(BUTTON_DOWN))
    {
        // Move the unit down one
        int destY = unit->y() + 1;

        return new MoveUnitCommand(unit, unit->x(), destY);
    }

    if (isPressed(BUTTON_LEFT))
    {
        // Move the unit left one
        int destX = unit->x() - 1;

        return new MoveUnitCommand(unit, destX, unit->y());
    }

    if (isPressed(BUTTON_RIGHT))
    {
        // Move the unit right one
        int destX = unit->x() + 1;

        return new MoveUnitCommand(unit, destX, unit->y());
    }

    return nullptr;
}