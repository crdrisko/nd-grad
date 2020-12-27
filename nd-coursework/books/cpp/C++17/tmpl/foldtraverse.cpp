// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: foldtraverse.cpp
// Author: crdrisko
// Date: 10/30/2020-06:57:37
// Description: Using fold expressions to traverse a binary tree

#include "foldtraverse.hpp"

#include <iostream>

int main()
{
    // init binary tree structure:
    Node* root = new Node {0};

    root->subLeft           = new Node {1};
    root->subLeft->subRight = new Node {2};

    // ...

    // traverse binary tree:
    Node* node = Node::traverse(root, Node::left, Node::right);
    std::cout << node->getValue() << '\n';
    node = root->*Node::left->*Node::right;
    std::cout << node->getValue() << '\n';
    node = root->subLeft->subRight;
    std::cout << node->getValue() << '\n';

    delete root->subLeft;
    delete root->subRight;
    delete root;
}
