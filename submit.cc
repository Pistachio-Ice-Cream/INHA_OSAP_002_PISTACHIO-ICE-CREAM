#include <algorithm>
#include <iostream>

template <typename value_type>
class Node {
 public:
  value_type key() const {
    return this->key_;
  }
  void set_key(value_type new_key) {
    key_ = new_key;
  }

 protected:
  value_type key_;
};
// clean
template <typename value_type>
class AVLTree;

template <typename value_type>
class treeNode : public Node<value_type> {
 public:
  int height() const {
    return height_;
  }
  void set_height(int new_height) {
    height_ = new_height;
  }
  void Balancing() {
    int height_of_left = 0, height_of_right = 0;
    bool is_root = true;
    if (left != nullptr) {
      height_of_left = left->height();
      is_root = false;
    }
    if (right != nullptr) {
      height_of_right = right->height();
      is_root = false;
    }
    if (is_root == true) {
      set_height(0);
    } else {
      set_height(std::max(height_of_left, height_of_right) + 1);
    }
  }

 public:
  treeNode* left = nullptr;
  treeNode* right = nullptr;
  treeNode* parent = nullptr;
  friend class AVLTree<value_type>;

 private:
  int height_ = 0;
};
// clean
template <typename value_type>
class AVLTree {
 public:
  treeNode<value_type>* root() {
    return root_;
  }
  AVLTree() {
    root_ = new treeNode<value_type>;
  };
  ~AVLTree(){

  };
  bool IsEmpty() {
    return node_counter_ == 0;
  };
  int Size() {
    return node_counter_;
  };
  treeNode<value_type>* InsertNode(treeNode<value_type>* iterator,
                                   value_type key_of_new_node) {
    if (IsEmpty()) {
      root_ = new treeNode<value_type>;
      root_->set_key(key_of_new_node);
      this->node_counter_++;
      return root_;
    }
    if (iterator == nullptr) {
      treeNode<value_type>* new_node = new treeNode<value_type>;
      this->node_counter_++;
      iterator = new_node; // 추가된 부분
      new_node->set_key(key_of_new_node);
      return new_node;
    } else if (iterator->key() < key_of_new_node) {
      iterator->right = InsertNode(iterator->right, key_of_new_node);
      // iterator->right->parent = iterator;
    } else {
      iterator->left = InsertNode(iterator->left, key_of_new_node);
      // iterator->left->parent = iterator;
    }
    iterator->set_height(
        (std::max(NodeHeight(iterator->left), NodeHeight(iterator->right))) +
        1);
    AdjustBlance(iterator, key_of_new_node);
    return iterator;
  };
  // iterator=new_node로 설정하는 부분 한 줄 추가했습니다.
  treeNode<value_type>* EraseNode(treeNode<value_type>* root_node,
                                  value_type key_of_target);
  treeNode<value_type>* FindNodePtr(value_type find_target) {
    treeNode<value_type>* iterator = root_;
    while (iterator != nullptr && iterator->key() != find_target) {
      iterator =
          (find_target < iterator->key()) ? iterator->left : iterator->right;
    }
    if (iterator == nullptr) {
      return nullptr;
    } else {
      return iterator;
    }
  };
  treeNode<value_type>* Minimum(value_type x) {
    treeNode<value_type>* iterator = FindNodePtr(x);
    while (iterator->left != nullptr) {
      iterator = iterator->left;
    }
    return iterator;
  };
  treeNode<value_type>* Maximum(value_type x) {
    treeNode<value_type>* iterator = FindNodePtr(x);
    while (iterator->right != nullptr) {
      iterator = iterator->right;
    }
    return iterator;
  };
  void Rank(value_type x);
  void Erase(value_type x);
  int NodeHeight(treeNode<value_type>* target_node) {
    if (target_node == nullptr) {
      return -1;
    }
    return target_node->height();
  };
  int FindDepth(value_type find_target) {
    treeNode<value_type>* iterator = root_;
    int depth_counter = 0;
    while (iterator != nullptr && iterator->key() != find_target) {
      depth_counter++;
      iterator =
          (find_target < iterator->key()) ? iterator->left : iterator->right;
    }
    return depth_counter;
  };

 protected:
  // clean;
  int CalculateBalance(treeNode<value_type>* target_node) {
    return NodeHeight(target_node->left) - NodeHeight(target_node->right);
  };
  treeNode<value_type>* LLRotation(treeNode<value_type>*& old_axis) {
    treeNode<value_type>* new_axis = old_axis->right;
    old_axis->right = new_axis->left;
    new_axis->left = old_axis;

    if (old_axis == root_) {
      root_ = new_axis;
    }
    old_axis->set_height(
        std::max(NodeHeight(old_axis->left), NodeHeight(old_axis->right)) + 1);
    new_axis->set_height(
        std::max(NodeHeight(new_axis->left), NodeHeight(new_axis->right)) + 1);
    return new_axis;
  }

  treeNode<value_type>* RRRotation(treeNode<value_type>*& old_axis) {
    treeNode<value_type>* new_axis = old_axis->left;
    old_axis->left = new_axis->right;
    new_axis->right = old_axis;
    if (old_axis == root_) {
      root_ = new_axis;
    }

    old_axis->set_height(
        std::max(NodeHeight(old_axis->left), NodeHeight(old_axis->right)) + 1);
    new_axis->set_height(
        std::max(NodeHeight(new_axis->left), NodeHeight(new_axis->right)) + 1);
    return new_axis;
  }
  // 주석은 기존 코드입니다.

  void AdjustBlance(treeNode<value_type>*& axis, value_type& target_key) {
    int balance_factor = CalculateBalance(axis);
    if (balance_factor == -1 || balance_factor == 0 || balance_factor == 1) {
      return;
    }
    if (balance_factor > 1 && target_key < axis->left->key()) { // ll상황
      axis = RRRotation(axis);
    } else if (balance_factor > 1 && target_key > axis->left->key()) { // lr상황
      axis->left = LLRotation(axis->left);
      axis = RRRotation(axis);
    } else if (balance_factor < -1 &&
               target_key > axis->right->key()) { // rr상황
      axis = LLRotation(axis);
    } else if (balance_factor < -1 &&
               target_key < axis->right->key()) { // rl상황
      axis->right = RRRotation(axis->right);
      axis = LLRotation(axis);
    }
  };

 protected:
  int node_counter_ = 0;
  treeNode<value_type>* root_;
};
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
    tree = AVLTree<value_type>();
  };
  ~AVLSet() {
    tree.~AVLTree();
  };
  void Minimum(value_type x) {
    if (tree.IsEmpty()) {
      return;
    } else {
      treeNode<value_type>* tmp = tree.Minimum(x);
      std::cout << tmp->key() << " " << tree.FindDepth(tmp->key()) << "\n";
    }
  };
  void Maximum(value_type x) {
    if (tree.IsEmpty()) {
      return;
    } else {
      treeNode<value_type>* tmp = tree.Maximum(x);
      std::cout << tmp->key() << " " << tree.FindDepth(tmp->key()) << "\n";
    }
  };
  void Empty() {
    std::cout << tree.IsEmpty() << "\n";
  };
  void Size() {
    std::cout << tree.Size() << "\n";
  };
  void Find(value_type x) {
    if (tree.FindNodePtr(x) == nullptr) {
      std::cout << "0"
                << "\n";
    } else {
      std::cout << tree.FindDepth(x) << "\n";
    }
  };
  void Insert(value_type x) {
    tree.InsertNode(tree.root(), x);
    std::cout << tree.FindDepth(x) << "\n";
  };
  // void Rank(value_type x);
  // void Erase(value_type x);

 private:
  AVLTree<value_type> tree;
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
    AVLSet<int> s;
    while (Q--) {
      std::string cmd;
      std::cin >> cmd;
      if (cmd == "minimum") {
        int x;
        std::cin >> x;
        s.Minimum(x);
      } else if (cmd == "maximum") {
        int x;
        std::cin >> x;
        s.Maximum(x);
      } else if (cmd == "empty") {
        s.Empty();
      } else if (cmd == "size") {
        s.Size();
      } else if (cmd == "find") {
        int x;
        std::cin >> x;
        s.Find(x);
      } else {
        int x;
        std::cin >> x;
        s.Insert(x);
      }
    }
  }
}