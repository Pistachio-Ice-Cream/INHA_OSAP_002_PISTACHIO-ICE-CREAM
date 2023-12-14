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

  bool LeftIsNull() {
    return left_ == nullptr;
  }
  bool RightIsNull() {
    return right_ == nullptr;
  }
  bool NoChild() {
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
  bool IsEmpty() const {
    return node_counter_ == 0;
  }
  int Size() const {
    return node_counter_;
  }
  TreeNode<value_type>* InsertNode(TreeNode<value_type>* iterator,
                                   value_type key_of_new_node) {
    /*
   노드 삽입 및 이에 따른 후처리 작업 함수
   iterator를 이 노드가 삽입돼야 할 위치로 이동시킨 후,
   있어야 할 빈 공간을 찾으면 해당 위치에 새로운 노드를 생성합니다.
   재귀적으로 부모 노드는 새로운 노드를 자식 노드로 포인팅합니다.
   */
    if (IsEmpty()) {
      // 만약 빈 트리라면, 루트 노드를 생성하고 바로 리턴합니다.
      root_ = new TreeNode<value_type>;
      root_->set_key(key_of_new_node);
      this->node_counter_++;
      return root_;
    }
    if (iterator == nullptr) {
      // iterator가 있어야 할 위치의 빈 공간을 찾았습니다.
      // 해당 위치에 새로운 노드를 추가합니다.
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
    // 새로운 노드를 삽입하는 재귀적 과정이 끝납니다.
    /*재귀적으로 자식 노드들로부터 Height를 계산해줍니다.
      새로 추가한 노드부터 리턴되며 재귀적으로 Height를 계산하게 될 것입니다.*/
    iterator->set_height(CalculateHeight(iterator));
    AdjustBalance(iterator, key_of_new_node);
    // AVL 트리의 균형 연산 완료 후에 현재 노드의 size_ 값을 업데이트
    iterator->set_size(CalculateSize(iterator));
    // 삽입 과정을 마친 후 밸런스 조정 함수로 넘어갑니다.
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
  TreeNode<value_type>* FindNodePtr(value_type find_target) const {
    TreeNode<value_type>* iterator = root_;
    while (iterator != nullptr && iterator->key() != find_target) {
      iterator =
          (find_target < iterator->key()) ? iterator->left_ : iterator->right_;
    }
    return iterator;
  }
  TreeNode<value_type>* Minimum(value_type x) const {
    TreeNode<value_type>* iterator = FindNodePtr(x);
    while (!iterator->LeftIsNull()) {
      iterator = iterator->left_;
    }
    return iterator;
  }
  TreeNode<value_type>* Maximum(value_type x) const {
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
  int FindDepth(value_type find_target) const {
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
  int CalculateSize(TreeNode<value_type>* target_node) const {
    return 1 + (!target_node->LeftIsNull() ? target_node->left_->size() : 0) +
           (!target_node->RightIsNull() ? target_node->right_->size() : 0);
  }
  int CalculateHeight(TreeNode<value_type>* target_node) const {
    return 1 + (std::max(NodeHeight(target_node->left_),
                         NodeHeight(target_node->right_)));
  }
  int CalculateBalance(TreeNode<value_type>* target_node) const {
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

  void AdjustBalance(TreeNode<value_type>*& axis, value_type& target_key) {
    // 축과 키를 기준으로 밸런스를 조정합니다.

    // balance_factor가 -1,0,1이면 AVLTree의 밸런스를 만족합니다. 조정 필요 x
    int balance_factor = CalculateBalance(axis);
    if (balance_factor == -1 || balance_factor == 0 || balance_factor == 1) {
      return;
    }
    // 왼쪽이 높고, 새로운 노드도 왼쪽에 있다.->오른쪽 로테이션 1번으로 해결
    // 왼쪽이 높고, 새로운 노드는 축 왼쪽에 있다.->좌회전-> 우회전
    // 오른쪽이 높고, 새로운 노드는 축 오른쪽에 있다.->우회전 한 번
    // 오른쪽이 높고, 새로운 노드는 축 왼쪽에 있다.->우회전->좌회전

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