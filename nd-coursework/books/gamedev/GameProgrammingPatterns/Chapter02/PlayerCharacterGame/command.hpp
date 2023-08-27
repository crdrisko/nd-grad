// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: command.hpp
// Author: crdrisko
// Date: 07/27/2022-09:28:23
// Description:

#ifndef COMMAND_HPP
#define COMMAND_HPP

class GameActor
{
public:
    void jump();
    void fireGun();
    void swapWeapon();
    void lurchIneffectively();
};

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute(GameActor& actor) = 0;
};

class JumpCommand : public Command
{
public:
    void execute(GameActor& actor) override { actor.jump(); }
};

class FireGunCommand : public Command
{
public:
    void execute(GameActor& actor) override { actor.fireGun(); }
};

class SwapWeaponCommand : public Command
{
public:
    void execute(GameActor& actor) override { actor.swapWeapon(); }
};

class LurchCommand : public Command
{
public:
    void execute(GameActor& actor) override { actor.lurchIneffectively(); }
};

#endif
