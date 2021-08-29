// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: PMWindowInterface.hpp
// Author: crdrisko
// Date: 07/26/2021-10:32:40
// Description:

#ifndef PMWINDOWINTERFACE_HPP
#define PMWINDOWINTERFACE_HPP

#include "../../ApendixC/point.hpp"

class HPS
{
};

struct PPOINTL
{
    Point x;
    Point y;
};

#define GPI_ERROR 1

bool GpiBeginPath(HPS, long);
bool GpiSetCurrentPosition(HPS, PPOINTL*);
int GpiPolyLine(HPS, long, PPOINTL*);
bool GpiEndPath(HPS);
void GpiStrokePath(HPS, long, long)

#endif
