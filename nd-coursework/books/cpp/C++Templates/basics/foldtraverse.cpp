// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: foldtraverse.cpp
// Author: crdrisko
// Date: 07/27/2020-10:50:22
// Description: Using a fold expression to traverse a path in a binary tree using operator->*

// define binary tree structure and traverse helpers:
struct Node
{
    int value;
    Node* left;
    Node* right;
    Node(int i = 0) : value {i}, left {nullptr}, right {nullptr} {}
    // ...
};

auto left  = &Node::left;
auto right = &Node::right;

// traverse tree, using fold expression:
template<typename T, typename... TP>
Node* traverse(T np, TP... paths)
{
    return (np->*...->*paths);   // np ->* paths1 ->* paths2 ->* ...
}

int main()
{
    // init binary tree structure:
    Node* root        = new Node {0};
    root->left        = new Node {1};
    root->left->right = new Node {2};
    // ...

    // traverse binary tree:
    Node* node = traverse(root, left, right);
    // ...
}
