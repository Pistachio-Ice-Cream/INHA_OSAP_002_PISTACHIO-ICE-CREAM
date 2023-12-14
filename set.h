/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23}.
*/
#ifndef SET_H
#define SET_H
#include "avl_tree.h"
template <typename value_type, typename Container>
class Set {
 public:
  Set(){};
  ~Set(){};
  virtual void Minimum(value_type x) const = 0;
  virtual void Maximum(value_type x) const = 0;
  virtual void Empty() const = 0;
  virtual void Size() const = 0;
  virtual void Find(value_type x) const = 0;
  virtual void Insert(value_type x) = 0;
  virtual void Rank(value_type x) = 0;
  virtual void Erase(value_type x) = 0;

 protected:
  Container container_;
};

template <typename value_type, typename Container>
class AVLSet : public Set<value_type, Container> {
 public:
  AVLSet() : container_(AVLTree<value_type>()) {
  }
  ~AVLSet() {
    container_.~AVLTree();
  }
  void Minimum(value_type x) const override {
    if (container_.IsEmpty()) {
      return;
    } else {
      TreeNode<value_type>* tmp = container_.Minimum(x);
      std::cout << tmp->key() << " " << container_.FindDepth(tmp->key())
                << "\n";
    }
  }
  void Maximum(value_type x) const override {
    if (container_.IsEmpty()) {
      return;
    } else {
      TreeNode<value_type>* tmp = container_.Maximum(x);
      std::cout << tmp->key() << " " << container_.FindDepth(tmp->key())
                << "\n";
    }
  }
  void Empty() const override {
    std::cout << container_.IsEmpty() << "\n";
  }
  void Size() const override {
    std::cout << container_.Size() << "\n";
  }
  void Find(value_type x) const override {
    if (container_.FindNodePtr(x) == nullptr) {
      std::cout << "0"
                << "\n";
    } else {
      std::cout << container_.FindDepth(x) << "\n";
    }
  }
  void Insert(value_type x) override {
    container_.InsertNode(container_.root(), x);
    std::cout << container_.FindDepth(x) << "\n";
  }
  void Rank(value_type x) override {
    if (container_.FindNodePtr(x) == nullptr) {
      std::cout << "0"
                << "\n";
    } else {
      std::cout << container_.FindDepth(x) << " "
                << container_.Rank(container_.root(), x) << "\n";
    }
  }
  void Erase(value_type x) override {
    if (container_.FindNodePtr(x) == nullptr) {
      std::cout << "0"
                << "\n";
    } else {
      std::cout << container_.FindDepth(x) << "\n";
      container_.EraseNode(container_.root(), x);
    }
  };

 private:
  AVLTree<value_type> container_;
};

#endif
