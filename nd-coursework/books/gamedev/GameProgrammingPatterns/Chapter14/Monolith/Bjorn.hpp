// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: Bjorn.hpp
// Author: crdrisko
// Date: 08/26/2023-11:21:17
// Description:

#ifndef BJORN_HPP
#define BJORN_HPP

class Volume
{
};

class Sprite
{
};

class World
{
public:
    void resolveCollision(Volume volume, int x, int y, int velocity);
};

class Graphics
{
public:
    void draw(Sprite sprite, int x, int y);
};

enum INPUTBUTTONS
{
    DIR_LEFT,
    DIR_RIGHT
};

class Controller
{
public:
    static INPUTBUTTONS getJoystickDirection();
};


class Bjorn
{
public:
    Bjorn() : velocity_(0), x_(0), y_(0) {}

    void update(World& world, Graphics& graphics);

private:
    static const int WALK_ACCELERATION = 1;

    int velocity_;
    int x_, y_;

    Volume volume_;

    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
};

void Bjorn::update(World& world, Graphics& graphics)
{
    // Apply user input to hero's velocity
    switch (Controller::getJoystickDirection())
    {
    case DIR_LEFT:
        velocity_ -= WALK_ACCELERATION;
        break;
    case DIR_RIGHT:
        velocity_ += WALK_ACCELERATION;
        break;
    }

    // Modify position by velocity
    x_ += velocity_;
    world.resolveCollision(volume_, x_, y_, velocity_);

    // Draw the appropriate sprite
    Sprite* sprite = &spriteStand_;

    if (velocity_ < 0)
        sprite = &spriteWalkLeft_;
    else if (velocity_ > 0)
        sprite = &spriteWalkRight_;

    graphics.draw(*sprite, x_, y_);
}

#endif
