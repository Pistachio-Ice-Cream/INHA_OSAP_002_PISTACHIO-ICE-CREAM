#include <algorithm>
#include <iostream>

template <typename value_type>
class Node {
 public:
  value_type get_key() {
    return this->key_;
  }

 protected:
  value_type key_;
};
// clean
template <typename value_type>
class AVLTree;

template <typename value_type>
class TreeNode : public Node<value_type> {
 public:
  int height_ = 0;
  TreeNode* left_ = nullptr;
  TreeNode* right_ = nullptr;
  friend class AVLTree<value_type>;
};
// clean
template <typename value_type>
class AVLTree {
 public:
  TreeNode<value_type>* root() {
    return root_;
  }
  AVLTree() : root_(new TreeNode<value_type>){};
  ~AVLTree(){};
  bool IsEmpty() {
    return node_counter_ == 0;
  };
  int Size() {
    return node_counter_;
  };
  TreeNode<value_type>* InsertNode(TreeNode<value_type>* iterator,
                                   value_type key_of_new_node) {
    if (IsEmpty()) {
      root_ = new TreeNode<value_type>;
      root_->key_ = key_of_new_node;
      this->node_counter_++;
      return root_;
    }
    if (iterator == nullptr) {
      TreeNode<value_type>* new_node = new TreeNode<value_type>;
      this->node_counter_++;
      iterator = new_node; // 추가된 부분
      new_node->key_ = key_of_new_node;
      return new_node;
    } else if (iterator->key_ < key_of_new_node) {
      iterator->right_ = InsertNode(iterator->right_, key_of_new_node);
      // iterator->right->parent = iterator;
    } else {
      iterator->left_ = InsertNode(iterator->left_, key_of_new_node);
      // iterator->left->parent = iterator;
    }
    iterator->height_ =
        (std::max(NodeHeight(iterator->left_), NodeHeight(iterator->right_))) +
        1;
    AdjustBlance(iterator, key_of_new_node);
    return iterator;
  };
  // iterator=new_node로 설정하는 부분 한 줄 추가했습니다.
  TreeNode<value_type>* EraseNode(TreeNode<value_type>* iterator,
                                  value_type key_of_target) {
    if (iterator->key_ < key_of_target) {
      iterator->right_ = EraseNode(iterator->right_, key_of_target);
      // iterator->right->parent = iterator;
    } else if (iterator->key_ > key_of_target) {
      iterator->left_ = EraseNode(iterator->left_, key_of_target);
      // iterator->left->parent = iterator;
    } else if (iterator->key_ == key_of_target) { // 삭제할 노드 도착
      if (Size() == 1) { // tree의 마지막 원소 삭제
        this->root_ = nullptr;
        delete iterator;
        this->node_counter_ = 0;
        return nullptr;
      }
      if (iterator->left_ == nullptr &&
          iterator->right_ == nullptr) { // 자식 노드가 없는 경우
        delete iterator;
        node_counter_--;
        return nullptr;
      } else if (iterator->left_ != nullptr && // 왼쪽 자식 노드만 있는 경우
                 iterator->right_ == nullptr) {
        if (this->root_ == iterator) {
          root_ = iterator->left_;
        }
        TreeNode<value_type>* successor = iterator->left_;
        delete iterator;
        node_counter_--;
        iterator = successor;
      } else if (iterator->left_ == nullptr && // 오른쪽 자식 노드만 있는 경우
                 iterator->right_ != nullptr) {
        if (this->root_ == iterator) {
          root_ = iterator->right_;
        }
        TreeNode<value_type>* successor = iterator->right_;
        node_counter_--;
        delete iterator;
        iterator = successor;
      } else if (iterator->left_ != nullptr &&
                 iterator->right_ != nullptr) { // 자식 노드가 2개인 경우
        TreeNode<value_type>* successor =
            Minimum(iterator->right_->key_); // 후임자 탐색
        iterator->key_ = successor->key_;
        successor->key_ = key_of_target; // 삭제할 노드와 후임자의 키 값 교환
        iterator->right_ =
            EraseNode(iterator->right_,
                      key_of_target); // 오른쪽 서브트리에서 successor를
                                      // 재귀적으로 삭제, 리밸런싱
      }
    }
    iterator->height_ =
        (std::max(NodeHeight(iterator->left_), NodeHeight(iterator->right_))) +
        1;
    AdjustBlance(iterator, key_of_target);
    return iterator;
  }
  TreeNode<value_type>* FindNodePtr(value_type find_target) {
    TreeNode<value_type>* iterator = root_;
    while (iterator != nullptr && iterator->key_ != find_target) {
      iterator =
          (find_target < iterator->key_) ? iterator->left_ : iterator->right_;
    }
    if (iterator == nullptr) {
      return nullptr;
    } else {
      return iterator;
    }
  };
  TreeNode<value_type>* Minimum(value_type x) {
    TreeNode<value_type>* iterator = FindNodePtr(x);
    while (iterator->left_ != nullptr) {
      iterator = iterator->left_;
    }
    return iterator;
  };
  TreeNode<value_type>* Maximum(value_type x) {
    TreeNode<value_type>* iterator = FindNodePtr(x);
    while (iterator->right_ != nullptr) {
      iterator = iterator->right_;
    }
    return iterator;
  };
  int Rank(value_type find_target) {
    TreeNode<value_type>* iterator = root_;
    int rank = 0;
    int& ref_rank = rank;
    Inorder(iterator, find_target, ref_rank);
    return rank;
  }
  int NodeHeight(TreeNode<value_type>* target_node) {
    if (target_node == nullptr) {
      return -1;
    }
    return target_node->height_;
  };
  int FindDepth(value_type find_target) {
    TreeNode<value_type>* iterator = root_;
    int depth_counter = 0;
    while (iterator != nullptr && iterator->key_ != find_target) {
      depth_counter++;
      iterator =
          (find_target < iterator->key_) ? iterator->left_ : iterator->right_;
    }
    return depth_counter;
  };

 protected:
  // clean;
  int CalculateBalance(TreeNode<value_type>* target_node) {
    return NodeHeight(target_node->left_) - NodeHeight(target_node->right_);
  };
  TreeNode<value_type>* LLRotation(TreeNode<value_type>*& old_axis) {
    TreeNode<value_type>* new_axis = old_axis->right_;
    old_axis->right_ = new_axis->left_;
    new_axis->left_ = old_axis;

    if (old_axis == root_) {
      root_ = new_axis;
    }
    old_axis->height_ =
        std::max(NodeHeight(old_axis->left_), NodeHeight(old_axis->right_)) + 1;
    new_axis->height_ =
        std::max(NodeHeight(new_axis->left_), NodeHeight(new_axis->right_)) + 1;
    return new_axis;
  }
  TreeNode<value_type>* RRRotation(TreeNode<value_type>*& old_axis) {
    TreeNode<value_type>* new_axis = old_axis->left_;
    old_axis->left_ = new_axis->right_;
    new_axis->right_ = old_axis;
    if (old_axis == root_) {
      root_ = new_axis;
    }
    old_axis->height_ =
        std::max(NodeHeight(old_axis->left_), NodeHeight(old_axis->right_)) + 1;
    new_axis->height_ =
        std::max(NodeHeight(new_axis->left_), NodeHeight(new_axis->right_)) + 1;
    return new_axis;
  }
  // 주석은 기존 코드입니다.
  void AdjustBlance(TreeNode<value_type>*& axis, value_type& target_key) {
    int balance_factor = CalculateBalance(axis);
    if (balance_factor == -1 || balance_factor == 0 || balance_factor == 1) {
      return;
    }
    if (balance_factor > 1 && target_key < axis->left_->key_) { // ll상황
      axis = RRRotation(axis);
    } else if (balance_factor > 1 && target_key > axis->left_->key_) { // lr상황
      axis->left_ = LLRotation(axis->left_);
      axis = RRRotation(axis);
    } else if (balance_factor < -1 &&
               target_key > axis->right_->key_) { // rr상황
      axis = LLRotation(axis);
    } else if (balance_factor < -1 &&
               target_key < axis->right_->key_) { // rl상황
      axis->right_ = RRRotation(axis->right_);
      axis = LLRotation(axis);
    }
  };
  void Inorder(TreeNode<value_type>* node, const value_type find_tarket, int& rank) {
    if(node == nullptr) {
      return;
    }
    // 왼쪽 서브트리로 재귀
    Inorder(node->left_, find_tarket, rank);
    // 만약 key값이 find_target 보다 작다면 rank를 높임 
    if(node->key_ <= find_tarket) {
      rank++;
    }
    // 오른쪽 서브트리로 재귀
    Inorder(node->right_, find_tarket, rank);
  }

 protected:
  int node_counter_ = 0;
  TreeNode<value_type>* root_;
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
  void Rank(value_type x){};
};

template <typename value_type>
class AVLSet : public Set<value_type> {
 public:
  AVLSet() : tree(AVLTree<value_type>()){};
  ~AVLSet() {
    tree.~AVLTree();
  };
  void Minimum(value_type x) {
    if (tree.IsEmpty()) {
      return;
    } else {
      TreeNode<value_type>* tmp = tree.Minimum(x);
      std::cout << tmp->get_key() << " " << tree.FindDepth(tmp->get_key())
                << "\n";
    }
  };
  void Maximum(value_type x) {
    if (tree.IsEmpty()) {
      return;
    } else {
      TreeNode<value_type>* tmp = tree.Maximum(x);
      std::cout << tmp->get_key() << " " << tree.FindDepth(tmp->get_key())
                << "\n";
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
  void Rank(value_type x) {
    if (tree.FindNodePtr(x) == nullptr) {
      std::cout << "0" << "\n";
    }
    else {
      std::cout << tree.FindDepth(x) << " " << tree.Rank(x) << "\n";
    }
 }
  void Erase(value_type x) {
    if (tree.FindNodePtr(x) == nullptr) {
      std::cout << "0\n";
    } else {
      std::cout << tree.FindDepth(x) << "\n";
      tree.EraseNode(tree.root(), x);
    }
  };

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
      } else if (cmd == "rank") {
        int x;
        std::cin >> x;
        s.Rank(x);
      } else if (cmd == "erase") {
        int x;
        std::cin >> x;
        s.Erase(x);
      } else {
        int x;
        std::cin >> x;
        s.Insert(x);
      }
    }
  }
}

/*
2
20
empty
insert 18
insert 17
insert 4
erase 17
find 18
insert 6
insert 19
insert 15
insert 1
rank 3
insert 2
minimum 18
rank 15
erase 6
insert 17
insert 14
insert 3
maximum 14
size
14
insert 14
erase 14
insert 17
insert 1
lnsert 8
empty
insert 18
insert 13
insert 16
rank 16
insert 19
find 8
erase 17
maximum 13

*/