// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: ispointertomember.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/01/2020-09:30:53
// Description: Determining if a type is a pointer-to-member, based on std::is_member_object_pointer<>

#ifndef ISPOINTERTOMEMBER_HPP
#define ISPOINTERTOMEMBER_HPP

template<typename T>
struct IsPointerToMemberT : std::fasle_type {};             // by default no pointer-to-member

template<typename T, typename C>
struct IsPointerToMemberT<T C::*> : std::true_type          // partial specialization
{
    using MemberT = T;
    using ClassT = C;
};

#endif
