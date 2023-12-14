/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23}.
*/
#ifndef SET_H
#define SET_H
#include "avl_tree.h"
template <typename value_type>
class Set {
 public:
  Set(){};
  ~Set(){};
  void Minimum(value_type x){};
  void Maximum(value_type x){};
  void Empty(){};
  void Size(){};
  void Find(value_type x){};
  void Insert(value_type x){};
};

template <typename value_type>
class AVLSet : public Set<value_type> {
 public:
  AVLSet() {
    container = AVLTree<value_type>();
  }
  ~AVLSet() {
    container.~AVLTree();
  }
  void Minimum(value_type x) {
    if (container.IsEmpty()) {
      return;
    } else {
      TreeNode<value_type>* tmp = container.Minimum(x);
      std::cout << tmp->key() << " " << container.FindDepth(tmp->key()) << "\n";
    }
  }
  void Maximum(value_type x) {
    if (container.IsEmpty()) {
      return;
    } else {
      TreeNode<value_type>* tmp = container.Maximum(x);
      std::cout << tmp->key() << " " << container.FindDepth(tmp->key()) << "\n";
    }
  }
  void Empty() {
    std::cout << container.IsEmpty() << "\n";
  }
  void Size() {
    std::cout << container.Size() << "\n";
  }
  void Find(value_type x) {
    if (container.FindNodePtr(x) == nullptr) {
      std::cout << "0"
                << "\n";
    } else {
      std::cout << container.FindDepth(x) << "\n";
    }
  }
  void Insert(value_type x) {
    container.InsertNode(container.root(), x);
    std::cout << container.FindDepth(x) << "\n";
  }
  // void Rank(value_type x);
  // void Erase(value_type x);

 private:
  AVLTree<value_type> container;
};

#endif
