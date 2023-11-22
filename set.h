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
  virtual void Minimum(value_type x);
  virtual void Maximum(value_type x);
  virtual void Empty();
  virtual void Size();
  virtual void Find(value_type x);
  virtual void Insert(value_type x);
  virtual void Rank(value_type x);
  virtual void Erase(value_type x);
};

template <typename value_type>
class AVLSet : public Set {
 public:
  AVLSet() {
    tree = AVLTree<value_type>();
  };
  ~AVLSet();
  void Minimum(value_type x);
  void Maximum(value_type x);
  void Empty();
  void Size();
  void Find(value_type x);
  void Insert(value_type x);
  void Rank(value_type x);
  void Erase(value_type x);

 private:
  AVLTree<value_type> tree;
};

#endif
