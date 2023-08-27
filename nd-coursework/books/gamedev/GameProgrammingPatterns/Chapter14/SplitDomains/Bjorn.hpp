// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: Bjorn.hpp
// Author: crdrisko
// Date: 08/27/2023-08:10:05
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
    int velocity;
    int x, y;

    void update(World& world, Graphics& graphics)
    {
        input_.update(*this);
        physics_.update(*this, world);
        graphics_.update(*this, graphics);
    }

private:
    InputComponent input_;
    PhysicsComponent physics_;
    GraphicsComponent graphics_;
};

class InputComponent
{
public:
    void update(Bjorn& bjorn)
    {
        switch (Controller::getJoystickDirection())
        {
        case DIR_LEFT:
            bjorn.velocity -= WALK_ACCELERATION;
            break;
        case DIR_RIGHT:
            bjorn.velocity += WALK_ACCELERATION;
            break;
        }
    }

private:
    static const int WALK_ACCELERATION = 1;
};

class PhysicsComponent
{
public:
    void update(Bjorn& bjorn, World& world)
    {
        bjorn.x += bjorn.velocity;
        world.resolveCollision(volume_, bjorn.x, bjorn.y, bjorn.velocity);
    }

private:
    Volume volume_;
};

class GraphicsComponent
{
public:
    void update(Bjorn& bjorn, Graphics& graphics)
    {
        Sprite* sprite = &spriteStand_;

        if (bjorn.velocity < 0)
            sprite = &spriteWalkLeft_;
        else if (bjorn.velocity > 0)
            sprite = &spriteWalkRight_;

        graphics.draw(*sprite, bjorn.x, bjorn.y);
    }

private:
    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
};

#endif
