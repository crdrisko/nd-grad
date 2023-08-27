// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: NoBjorn.hpp
// Author: crdrisko
// Date: 08/27/2023-08:27:07
// Description:

#ifndef NOBJORN_HPP
#define NOBJORN_HPP

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

class GameObject
{
public:
    int velocity;
    int x, y;

    GameObject(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
        : input_(input), physics_(physics), graphics_(graphics)
    {
    }

    void update(World& world, Graphics& graphics)
    {
        input_->update(*this);
        physics_->update(*this, world);
        graphics_->update(*this, graphics);
    }

private:
    InputComponent* input_;
    PhysicsComponent* physics_;
    GraphicsComponent* graphics_;
};

class InputComponent
{
public:
    virtual ~InputComponent() {}
    virtual void update(GameObject& object) = 0;
};

class PhysicsComponent
{
public:
    virtual ~PhysicsComponent() {}
    virtual void update(GameObject& object, World& world) = 0;
};

class GraphicsComponent
{
public:
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject& object, Graphics& graphics) = 0;
};

class PlayerInputComponent : public InputComponent
{
public:
    virtual void update(GameObject& obj)
    {
        switch (Controller::getJoystickDirection())
        {
        case DIR_LEFT:
            obj.velocity -= WALK_ACCELERATION;
            break;
        case DIR_RIGHT:
            obj.velocity += WALK_ACCELERATION;
            break;
        }
    }

private:
    static const int WALK_ACCELERATION = 1;
};

class BjornPhysicsComponent : public PhysicsComponent
{
public:
    virtual void update(GameObject& obj, World& world)
    {
        obj.x += obj.velocity;
        world.resolveCollision(volume_, obj.x, obj.y, obj.velocity);
    }

private:
    Volume volume_;
};

class BjornGraphicsCompontent : public GraphicsComponent
{
public:
    virtual void update(GameObject& obj, Graphics& graphics)
    {
        Sprite* sprite = &spriteStand_;

        if (obj.velocity < 0)
            sprite = &spriteWalkLeft_;
        else if (obj.velocity > 0)
            sprite = &spriteWalkRight_;

        graphics.draw(*sprite, obj.x, obj.y);
    }

private:
    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
};

GameObject* createBjorn()
{
    return new GameObject(new PlayerInputComponent(), new BjornPhysicsComponent(), new BjornGraphicsCompontent());
}

#endif
