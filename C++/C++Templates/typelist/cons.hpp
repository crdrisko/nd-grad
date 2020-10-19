// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: cons.hpp
// Author: crdrisko
// Date: 10/02/2020-08:35:45
// Description: A precursor to typelists when variadic templates didn't exist in the language standard

#ifndef CONS_HPP
#define CONS_HPP

class Nil {};

template<typename HeadT, typename TailT = Nil>
class Cons
{
public:
    using Head = HeadT;
    using Tail = TailT;
};

#endif
