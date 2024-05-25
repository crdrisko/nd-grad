// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: foldtraverse.hpp
// Author: crdrisko
// Date: 10/30/2020-06:52:10
// Description: Define a binary tree structure and traverse helpers

#ifndef FOLDTRAVERSE_HPP
#define FOLDTRAVERSE_HPP

struct Node
{
    int value;
    Node* subLeft {nullptr};
    Node* subRight {nullptr};

    Node(int i = 0) : value {i} {}

    int getValue() const { return value; }

    // ...

    // traverse helpers:
    static constexpr auto left  = &Node::subLeft;
    static constexpr auto right = &Node::subRight;

    // traverse tree, using fold expression:
    template<typename T, typename... TP>
    static Node* traverse(T np, TP... paths)
    {
        return (np->*...->*paths);   // np ->* paths1 ->* paths2 ...
    }
};

#endif
