// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: composite.cpp
// Author: crdrisko
// Date: 07/31/2021-07:35:16
// Description: Compose objects into tree structures to represent part-whole hierarchies

#include "composite.hpp"

#include <iostream>

Currency CompositeEquipment::NetPrice()
{
    Iterator<Equipment*>* i = CreateIterator();
    Currency total          = 0;

    for (i->First(); !i->IsDone(); i->Next())
    {
        total += i->CurrentItem()->NetPrice();
    }

    delete i;

    return total;
}

int main()
{
    Cabinet* cabinet = new Cabinet("PC Cabinet");
    Chassis* chassis = new Chassis("PC Chassis");

    cabinet->Add(chassis);

    Bus* bus = new Bus("MCA Bus");
    bus->Add(new Card("16Mbs Token Ring"));

    chassis->Add(bus);
    chassis->Add(new FloppyDisk("3.5in Floppy"));

    std::cout << "The net price is " << chassis->NetPrice() << std::endl;
}
