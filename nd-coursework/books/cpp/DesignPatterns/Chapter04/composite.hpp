// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: composite.hpp
// Author: crdrisko
// Date: 07/31/2021-07:35:14
// Description: Compose objects into tree structures to represent part-whole hierarchies

#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "../ApendixC/iterator.hpp"
#include "../ApendixC/list.hpp"

using Watt     = double;
using Currency = double;

// Component - declares the interface for objects in the composition
class Equipment
{
public:
    virtual ~Equipment();

    const char* Name() { return _name; }

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();

    virtual void Add(Equipment*);
    virtual void Remove(Equipment*);
    virtual Iterator<Equipment*>* CreateIterator();

protected:
    Equipment(const char*);

private:
    const char* _name;
};

// Leaf - defines behavior for primitive objects in the composition
class FloppyDisk : public Equipment
{
public:
    FloppyDisk(const char*);
    virtual ~FloppyDisk();

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();
};

// Leaf - defines behavior for primitive objects in the composition
class Card : public Equipment
{
public:
    Card(const char*);
    virtual ~Card();

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();
};

// Composite - defines behavior for components having children and stores child components
class CompositeEquipment : public Equipment
{
public:
    virtual ~CompositeEquipment();

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();

    virtual void Add(Equipment*);
    virtual void Remove(Equipment*);
    virtual Iterator<Equipment*>* CreateIterator();

protected:
    CompositeEquipment(const char*);

private:
    List<Equipment*> _equipment;
};

// Composite - defines behavior for components having children and stores child components
class Chassis : public CompositeEquipment
{
public:
    Chassis(const char*);
    virtual ~Chassis();

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();
};

// Composite - defines behavior for components having children and stores child components
class Cabinet : public CompositeEquipment
{
public:
    Cabinet(const char*);
    virtual ~Cabinet();

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();
};

// Composite - defines behavior for components having children and stores child components
class Bus : public CompositeEquipment
{
public:
    Bus(const char*);
    virtual ~Bus();

    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();
};

#endif
