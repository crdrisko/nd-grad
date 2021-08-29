// Copyright (c) 1995 by Addison-Wesley. All rights reserved.
//
// Name: bridge.hpp
// Author: crdrisko
// Date: 07/26/2021-09:44:39
// Description: Decouple an abstraction from its implementation so that the two can vary independently

#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "../ApendixC/point.hpp"
#include "Include/PMWindowInterface.hpp"
#include "Include/XWindowInterface.hpp"

class Window;
class WindowImp;

class WindowSystemFactory
{
public:
    static WindowSystemFactory* Instance();

    WindowImp* MakeWindowImp();

protected:
    WindowSystemFactory();

private:
    static WindowSystemFactory* _instance;
};

class View
{
public:
    void DrawOn(Window*) {}
};

// Abstraction - defines the abstraction's interface and maintains a reference to an object of type Implementor
class Window
{
public:
    Window(View* contents);

    // requests handled by window
    virtual void DrawContents();

    virtual void Open();
    virtual void Close();
    virtual void Iconify();
    virtual void Deiconify();

    // requests forwarded to implementation
    virtual void SetOrigin(const Point& at);
    virtual void SetExtent(const Point& extent);
    virtual void Raise();
    virtual void Lower();

    virtual void DrawLine(const Point&, const Point&);
    virtual void DrawRect(const Point&, const Point&);
    virtual void DrawPolygon(const Point[], int n);
    virtual void DrawText(const char*, const Point&);

protected:
    WindowImp* GetWindowImp();
    View* GetView();

private:
    WindowImp* _imp;
    View* _contents;   // the window's contents
};

// Implementor - defines the interface for implementation classes
class WindowImp
{
public:
    virtual void ImpTop()                   = 0;
    virtual void ImpBottom()                = 0;
    virtual void ImpSetExtent(const Point&) = 0;
    virtual void ImpSetOrigin(const Point&) = 0;

    virtual void DeviceRect(Coord, Coord, Coord, Coord)  = 0;
    virtual void DeviceText(const char*, Coord, Coord)   = 0;
    virtual void DeviceBitmap(const char*, Coord, Coord) = 0;
    // lots more functions for drawing on windows...

protected:
    WindowImp();
};

// Refined Abstraction - extends the interface defined by Abstraction
class ApplicationWindow : public Window
{
public:
    // ...
    virtual void DrawContents();
};

// Refined Abstraction - extends the interface defined by Abstraction
class IconWindow : public Window
{
public:
    // ...
    virtual void DrawContents();

private:
    const char* _bitmapName;
};

// Concrete Implementor - implements the Implementor interface and defines its concrete implementation
class XWindowImp : public WindowImp
{
public:
    XWindowImp();

    virtual void DeviceRect(Coord, Coord, Coord, Coord);
    // remainder of public interface...

private:
    // lots of X window system-specific state, including:
    Display* _dpy;
    Drawable _winid;   // window id
    GC _gc;            // window graphic context
};

// Concrete Implementor - implements the Implementor interface and defines its concrete implementation
class PMWindowImp : public WindowImp
{
public:
    PMWindowImp();

    virtual void DeviceRect(Coord, Coord, Coord, Coord);
    // remainder of public interface...

private:
    // lots of PM window system-specific state, including:
    HPS _hps;
};

#endif
