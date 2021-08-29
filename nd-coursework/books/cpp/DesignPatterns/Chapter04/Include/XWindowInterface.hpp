// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: XWindowInterface.hpp
// Author: crdrisko
// Date: 07/26/2021-10:32:30
// Description:

#ifndef XWINDOWINTERFACE_HPP
#define XWINDOWINTERFACE_HPP

class Display
{
};

class Drawable
{
};

class GC
{
};

void XDrawRectangle(Display*, Drawable, GC, int, int, int, int);

#endif
