// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: exprops1.hpp
// Author: crdrisko
// Date: 09/29/2020-07:19:39
// Description: Possible definitions for the operands of the expression templates

#ifndef EXPROPS1_HPP
#define EXPROPS1_HPP

#include <cassert>
#include <cstddef>

// include helper class traits template to select whether to refer to an
// expression template node either by value or by reference
#include "exprops1a.hpp"

// class for objects that represent the addition of two operands
template<typename T, typename OP1, typename OP2>
class A_Add
{
private:
    typename A_Traits<OP1>::ExprRef op1;   // first operand
    typename A_Traits<OP2>::ExprRef op2;   // second operand

public:
    // constructor initializes references to operands
    A_Add(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}

    // compute sum when value requested
    T operator[](std::size_t idx) const { return op1[idx] + op2[idx]; }

    // size is maximum size
    std::size_t size() const
    {
        assert(op1.size() == 0 || op2.size() == 0 || op1.size() == op2.size());

        return op1.size() != 0 ? op1.size() : op2.size();
    }
};

// class for objects that represent the multiplication of two operands
template<typename T, typename OP1, typename OP2>
class A_Mult
{
private:
    typename A_Traits<OP1>::ExprRef op1;   // first operand
    typename A_Traits<OP2>::ExprRef op2;   // second operand

public:
    // constructor initializes references to operands
    A_Mult(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}

    // compute product when value requested
    T operator[](std::size_t idx) const { return op1[idx] * op2[idx]; }

    // size is maximum size
    std::size_t size() const
    {
        assert(op1.size() == 0 || op2.size() == 0 || op1.size() == op2.size());

        return op1.size() != 0 ? op1.size() : op2.size();
    }
};

#endif
