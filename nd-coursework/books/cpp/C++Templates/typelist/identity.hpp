// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: identity.hpp
// Author: crdrisko
// Date: 10/01/2020-18:01:27
// Description: Yield T when using member Type

#ifndef IDENTITY_HPP
#define IDENTITY_HPP

template<typename T>
struct IdentityT
{
    using Type = T;
};


#endif
