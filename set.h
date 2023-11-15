/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23}.
*/
#ifndef SET_H
#define SET_H
#include "avl_tree.h"
class Set : public AVLTree
{
public:
    Set() {
        tree = AVLTree();
    }
    void minimum(int X);
    void maximum(int X);
    void empty() {
        std::cout << tree.IsEmpty();
    }
    void size() {
        std::cout << tree.Size();
    }
    void find(int x);
    void insert(int x);
    void rank(int x);
    void erase(int x);

private:
    AVLTree tree;
};
#endif // SET_H
