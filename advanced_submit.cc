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
class TreeNode : public Node<value_type> {
 public:
  int height() const {
    return height_;
  }
  void set_height(int new_height) {
    height_ = new_height;
  }
  int size() const {
    return size_;
  }
  void set_size(int new_size) {
    size_ = new_size;
  }

  boolean LeftIsNull() {
    return left_ == nullptr;
  }
  boolean RightIsNull() {
    return right_ == nullptr;
  }
  boolean NoChild() {
    return ((left_ == nullptr) && (right_ == nullptr));
  }

 public:
  TreeNode* left_ = nullptr;
  TreeNode* right_ = nullptr;
  friend class AVLTree<value_type>;

 private:
  int height_ = 0;
  int size_ = 1;
};
// clean
template <typename value_type>
class AVLTree {
 public:
  TreeNode<value_type>* root() const {
    return root_;
  }
  AVLTree() {
    root_ = new TreeNode<value_type>;
  }
  AVLTree(const AVLTree& copy_target) {
    root_ = CopyTree(copy_target.root());
  }
  ~AVLTree() {
  }
  bool IsEmpty() {
    return node_counter_ == 0;
  }
  int Size() {
    return node_counter_;
  }
  TreeNode<value_type>* InsertNode(TreeNode<value_type>* iterator,
                                   value_type key_of_new_node) {
    if (IsEmpty()) {
      root_ = new TreeNode<value_type>;
      root_->set_key(key_of_new_node);
      this->node_counter_++;
      return root_;
    }
    if (iterator == nullptr) {
      TreeNode<value_type>* new_node = new TreeNode<value_type>;
      this->node_counter_++;
      iterator = new_node;
      new_node->set_key(key_of_new_node);
      return new_node;
    } else if (iterator->key() < key_of_new_node) {
      iterator->right_ = InsertNode(iterator->right_, key_of_new_node);
    } else {
      iterator->left_ = InsertNode(iterator->left_, key_of_new_node);
    }
    iterator->set_height(CalculateHeight(iterator));
    AdjustBalance(iterator, key_of_new_node);
    // AVL 트리의 균형 연산 완료 후에 현재 노드의 size_ 값을 업데이트
    iterator->set_size(CalculateSize(iterator));
    
    return iterator;
  }
  // iterator=new_node로 설정하는 부분 한 줄 추가했습니다.
  TreeNode<value_type>* EraseNode(TreeNode<value_type>* iterator,
                                  value_type key_of_target) {
    if (iterator->key() == key_of_target) { // 삭제할 노드 도착
      if (Size() == 1) {                    // tree의 마지막 원소 삭제
        delete iterator;
        this->root_ = nullptr;
        this->node_counter_ = 0;
        return nullptr;
      }
      if (iterator->NoChild()) { // 자식 노드가 없는 경우
        delete iterator;
        node_counter_--;
        return nullptr;
      } else if (!iterator->LeftIsNull() && // 왼쪽 자식 노드만 있는 경우
                 iterator->RightIsNull()) {
        if (this->root_ == iterator) {
          root_ = iterator->left_;
        }
        TreeNode<value_type>* successor = iterator->left_;
        node_counter_--;
        delete iterator;
        return successor;
      } else if (iterator->LeftIsNull() && // 오른쪽 자식 노드만 있는 경우
                 !iterator->RightIsNull()) {
        if (this->root_ == iterator) {
          root_ = iterator->right_;
        }
        TreeNode<value_type>* successor = iterator->right_;
        node_counter_--;
        delete iterator;
        return successor;
      } else if (!iterator->LeftIsNull() &&
                 !iterator->RightIsNull()) { // 자식 노드가 2개인 경우
        TreeNode<value_type>* successor =
            Minimum(iterator->right_->key()); // 후임자 탐색
        iterator->set_key(successor->key());
        successor->set_key(key_of_target); // 삭제할 노드와 후임자의 키 값 교환
        iterator->right_ =
            EraseNode(iterator->right_,
                      key_of_target); // 오른쪽 서브트리에서 successor를
                                      // 재귀적으로 삭제, 리밸런싱
      }
    } else if (iterator->key() < key_of_target) {
      iterator->right_ = EraseNode(iterator->right_, key_of_target);
      // iterator->right->parent = iterator;
    } else if (iterator->key() > key_of_target) {
      iterator->left_ = EraseNode(iterator->left_, key_of_target);
      // iterator->left->parent = iterator;
    }
    iterator->set_height(CalculateHeight(iterator));
    if (iterator != nullptr) {
      AdjustBalance(iterator, key_of_target);
    }
    // AVL 트리의 균형 연산 완료 후에 현재 노드의 size_ 값을 업데이트
    iterator->set_size(CalculateSize(iterator));
    return iterator;
  }
  TreeNode<value_type>* FindNodePtr(value_type find_target) {
    TreeNode<value_type>* iterator = root_;
    while (iterator != nullptr && iterator->key() != find_target) {
      iterator =
          (find_target < iterator->key()) ? iterator->left_ : iterator->right_;
    }
    return iterator;
  }
  TreeNode<value_type>* Minimum(value_type x) {
    TreeNode<value_type>* iterator = FindNodePtr(x);
    while (!iterator->LeftIsNull()) {
      iterator = iterator->left_;
    }
    return iterator;
  }
  TreeNode<value_type>* Maximum(value_type x) {
    TreeNode<value_type>* iterator = FindNodePtr(x);
    while (!iterator->RightIsNull()) {
      iterator = iterator->right_;
    }
    return iterator;
  }
  int Rank(TreeNode<value_type>* target_node, value_type x) {
    if (target_node == nullptr) {
      return 0;
    }
    if (target_node->key() <= x) {
      if (target_node->LeftIsNull()) {
        return 1 + Rank(target_node->right_, x);
      } else {
        return 1 + target_node->left_->size() + Rank(target_node->right_, x);
      }
    } else {
      return Rank(target_node->left_, x);
    }  
  }
  int NodeHeight(TreeNode<value_type>* target_node) const {
    if (target_node == nullptr) {
      return -1;
    }
    return target_node->height();
  }
  int FindDepth(value_type find_target) {
    TreeNode<value_type>* iterator = root_;
    int depth_counter = 0;
    while (iterator != nullptr && iterator->key() != find_target) {
      depth_counter++;
      iterator =
          (find_target < iterator->key()) ? iterator->left_ : iterator->right_;
    }
    return depth_counter;
  }

 protected:
  int CalculateSize(TreeNode<value_type>* target_node) {
    return 1 + (!target_node->LeftIsNull() ? target_node->left_->size() : 0)
      + (!target_node->RightIsNull() ? target_node->right_->size() : 0);
  }
  int CalculateHeight(TreeNode<value_type>* target_node) {
    return 1 + (std::max(NodeHeight(target_node->left_), NodeHeight(target_node->right_)));
  }
  int CalculateBalance(TreeNode<value_type>* target_node) {
    if (target_node == nullptr) {
      return 0;
    }
    return NodeHeight(target_node->left_) - NodeHeight(target_node->right_);
  };
  TreeNode<value_type>* LLRotation(TreeNode<value_type>*& old_axis) {
    if (old_axis->RightIsNull()) {
      return old_axis;
    }
    TreeNode<value_type>* new_axis = old_axis->right_;
    old_axis->right_ = new_axis->left_;
    new_axis->left_ = old_axis;

    if (old_axis == root_) {
      root_ = new_axis;
    }
    old_axis->set_height(CalculateHeight(old_axis));
    new_axis->set_height(CalculateHeight(new_axis));

    old_axis->set_size(CalculateSize(old_axis));
    new_axis->set_size(CalculateSize(new_axis));

    return new_axis;
  }

  TreeNode<value_type>* RRRotation(TreeNode<value_type>*& old_axis) {
    if (old_axis->LeftIsNull()) {
      return old_axis;
    }
    TreeNode<value_type>* new_axis = old_axis->left_;
    old_axis->left_ = new_axis->right_;
    new_axis->right_ = old_axis;
    if (old_axis == root_) {
      root_ = new_axis;
    }
    old_axis->set_height(CalculateHeight(old_axis));
    new_axis->set_height(CalculateHeight(new_axis));

    old_axis->set_size(CalculateSize(old_axis));
    new_axis->set_size(CalculateSize(new_axis));
    
    return new_axis;
  }
  // 주석은 기존 코드입니다.

  void AdjustBalance(TreeNode<value_type>*& axis, value_type& target_key) {
    int balance_factor = CalculateBalance(axis);
    if (balance_factor == -1 || balance_factor == 0 || balance_factor == 1) {
      return;
    }

    if (balance_factor > 1) {
      balance_factor = CalculateBalance(axis->left_);
      if (balance_factor >= 0) {
        axis = RRRotation(axis);
      } else {
        axis->left_ = LLRotation(axis->left_);
        axis = RRRotation(axis);
      }
    } else if (balance_factor < -1) {
      balance_factor = CalculateBalance(axis->right_);
      if (balance_factor <= 0) {
        axis = LLRotation(axis);
      } else {
        axis->right_ = RRRotation(axis->right_);
        axis = LLRotation(axis);
      }
    }
  }

 protected:
  int node_counter_ = 0;
  TreeNode<value_type>* root_;

  TreeNode<value_type>* CopyTree(const TreeNode<value_type>* node) {
    if (node == nullptr) {
      return nullptr;
    }

    TreeNode<value_type>* new_node = new TreeNode<value_type>;
    new_node->set_key(node->key());
    new_node->left_ = CopyTree(node->left_);
    new_node->right_ = CopyTree(node->right_);
    new_node->set_height(node->height());

    return new_node;
  }
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
  void Erase(value_type x){};
};

template <typename value_type>
class AVLSet : public Set<value_type> {
 public:
  AVLSet() {
    tree = AVLTree<value_type>();
  }
  ~AVLSet() {
    tree.~AVLTree();
  }
  void Minimum(value_type x) {
    if (tree.IsEmpty()) {
      return;
    } else {
      TreeNode<value_type>* tmp = tree.Minimum(x);
      std::cout << tmp->key() << " " << tree.FindDepth(tmp->key()) << "\n";
    }
  }
  void Maximum(value_type x) {
    if (tree.IsEmpty()) {
      return;
    } else {
      TreeNode<value_type>* tmp = tree.Maximum(x);
      std::cout << tmp->key() << " " << tree.FindDepth(tmp->key()) << "\n";
    }
  }
  void Empty() {
    std::cout << tree.IsEmpty() << "\n";
  }
  void Size() {
    std::cout << tree.Size() << "\n";
  }
  void Find(value_type x) {
    if (tree.FindNodePtr(x) == nullptr) {
      std::cout << "0"
                << "\n";
    } else {
      std::cout << tree.FindDepth(x) << "\n";
    }
  }
  void Insert(value_type x) {
    tree.InsertNode(tree.root(), x);
    std::cout << tree.FindDepth(x) << "\n";
  }
  void Rank(value_type x) {
    if (tree.FindNodePtr(x) == nullptr) {
      std::cout << "0" << "\n";
    }
    else {
      std::cout << tree.FindDepth(x) << " " << tree.Rank(tree.root(), x) << "\n";
    }
  }
  void Erase(value_type x) {
    if (tree.FindNodePtr(x) == nullptr) {
      std::cout << "0"
                << "\n";
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
      } else if (cmd == "insert") {
        int x;
        std::cin >> x;
        s.Insert(x);
      }
    }
  }
}