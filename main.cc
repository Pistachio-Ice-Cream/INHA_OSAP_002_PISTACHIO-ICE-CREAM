/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23}.
*/
#include <iostream>

#include "avl_tree.h"
#include "nodes.h"
#include "set.h"

template <typename value_type, typename Container>
class UserInterface {
 public:
  UserInterface(Container& container) : object_(container) {
  }
  void minimum(value_type x) {
    object_.Minimum(x);
  }
  void maximum(value_type x) {
    object_.Maximum(x);
  }
  void empty() {
    object_.Empty();
  }
  void size() {
    object_.Size();
  }
  void find(value_type x) {
    object_.Find(x);
  }
  void insert(value_type x) {
    object_.Insert(x);
  }
  void rank(value_type x) {
    object_.Rank(x);
  }
  void erase(value_type x) {
    object_.Erase(x);
  }

 private:
  Container& object_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  int T;
  std::cin >> T;
  while (T--) {
    int Q;
    std::cin >> Q;
    Set<int, AVLTree<int>>* container = new AVLSet<int, AVLTree<int>>();
    UserInterface<int, Set<int, AVLTree<int>>> ui(*container);
    while (Q--) {
      std::string cmd;
      std::cin >> cmd;
      if (cmd == "minimum") {
        int x;
        std::cin >> x;
        ui.minimum(x);
      } else if (cmd == "maximum") {
        int x;
        std::cin >> x;
        ui.maximum(x);
      } else if (cmd == "empty") {
        ui.empty();
      } else if (cmd == "size") {
        ui.size();
      } else if (cmd == "find") {
        int x;
        std::cin >> x;
        ui.find(x);
      } else if (cmd == "rank") {
        int x;
        std::cin >> x;
        ui.rank(x);
      } else if (cmd == "erase") {
        int x;
        std::cin >> x;
        ui.erase(x);
      } else if (cmd == "insert") {
        int x;
        std::cin >> x;
        ui.insert(x);
      }
    }
  }
}