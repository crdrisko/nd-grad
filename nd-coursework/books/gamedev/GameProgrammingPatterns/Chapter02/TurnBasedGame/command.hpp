// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: command.hpp
// Author: crdrisko
// Date: 07/27/2022-09:28:23
// Description:

#ifndef COMMAND_HPP
#define COMMAND_HPP

class Unit
{
private:
    int x_;
    int y_;

public:
    void moveTo(int x, int y);

    int& x() { return x_; }
    const int& x() const { return x_; }

    int& y() { return y_; }
    const int& y() const { return y_; }
};

Unit* getSelectedUnit();

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute() = 0;
    virtual void undo()    = 0;
};

class MoveUnitCommand : public Command
{
private:
    Unit* unit_;
    int x_, y_;
    int xBefore_, yBefore_;

public:
    MoveUnitCommand(Unit* unit, int x, int y) : unit_ {unit}, x_ {x}, y_ {y}, xBefore_ {0}, yBefore_ {0} {}

    void execute() override
    {
        // Remember the unit's position before the move so we can restore it
        xBefore_ = unit_->x();
        yBefore_ = unit_->y();

        unit_->moveTo(x_, y_);
    }

    void undo() override { unit_->moveTo(xBefore_, yBefore_); }
};

#endif
