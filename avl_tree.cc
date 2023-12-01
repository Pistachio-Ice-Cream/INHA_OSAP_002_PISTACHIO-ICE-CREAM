/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23, rla1wo23@gmail.com}.
*/
#include "avl_tree.h"
/*
함수의 구현부입니다.
getter와 setter는 주석을 생략함.
*/

/*Node Class Functions start*/
template <typename value_type>
value_type Node<value_type>::key() const {
  return key_;
}

template <typename value_type>
void Node<value_type>::set_key(value_type new_key) {
  key_ = new_key;
}
/*Node Class Functions end*/

/*TreeNode Class Functions start*/
template <typename value_type>
int TreeNode<value_type>::height() const {
  return height_;
}
template <typename value_type>
void TreeNode<value_type>::set_height(int new_height) {
  height_ = new_height;
}
template <typename value_type>
void TreeNode<value_type>::Balancing() { // 자식 노드들로부터 본인의 height를
                                         // 계산 후 조정합니다.
  int height_of_left = -1, height_of_right = -1;
  if (left_ != nullptr) {
    height_of_left = left_->height();
  }
  if (right_ != nullptr) {
    height_of_right = right_->height();
  }
  set_height(std::max(height_of_left, height_of_right) + 1); // height의 정의
}
/*TreeNode Class Functions end*/

/*AVLTree Class Functions start*/
// public method
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::root() const {
  return root_;
}
template <typename value_type>
AVLTree<value_type>::AVLTree() : root_(nullptr) {
  return root_;
}
template <typename value_type>
AVLTree<value_type>::AVLTree(const AVLTree &copy_target) {
  root_ = CopyTree(copy_target.root());
}
template <typename value_type>
AVLTree<value_type>::~AVLTree() { // 소멸자 구현은 추후에
}
template <typename value_type>
bool AVLTree<value_type>::IsEmpty() {
  return node_counter_ == 0;
}

template <typename value_type>
int AVLTree<value_type>::Size() {
  return node_counter_;
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::InsertNode(
    TreeNode<value_type> *iterator, value_type key_of_new_node) {
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
    TreeNode<value_type> *new_node = new TreeNode<value_type>;
    this->node_counter_++;
    iterator = new_node; // 추가된 부분
    new_node->set_key(key_of_new_node);
    return new_node;
  } else if (iterator->key() < key_of_new_node) {
    // 빈 공간을 못 찾았고, 만약 새로운 노드가 부모 노드보다 작다면 왼쪽으로,
    //  크다면 오른쪽으로 iterator를 이동시킵니다.
    iterator->right_ = InsertNode(iterator->right_, key_of_new_node);
  } else {
    iterator->left_ = InsertNode(iterator->left_, key_of_new_node);
  }
  // 새로운 노드를 삽입하는 재귀적 과정이 끝납니다.
  iterator->set_height(
      (std::max(NodeHeight(iterator->left_), NodeHeight(iterator->right_))) +
      1);
  /*재귀적으로 자식 노드들로부터 Height를 계산해줍니다.
  새로 추가한 노드부터 리턴되며 재귀적으로 Height를 계산하게 될 것입니다.*/
  AdjustBalance(iterator, key_of_new_node);
  // 삽입 과정을 마친 후 밸런스 조정 함수로 넘어갑니다.
  return iterator;
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::FindNodePtr(value_type find_target) {
  // 원하는 키를 가진 노드의 포인터를 반환합니다.
  TreeNode<value_type> *iterator = root_;
  /*root_부터 iterating 시작,작다면 왼쪽으로, 크다면 오른쪽으로 iterator 이동.
만약 키와 같다면, 거기서 탐색 종료*/
  while (iterator != nullptr && iterator->key() != find_target) {
    iterator =
        (find_target < iterator->key()) ? iterator->left_ : iterator->right_;
  }
  return iterator;
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::Minimum(value_type x) {
  /* x를 루트로하는 서브트리를 찾아서, 반복자를 거기서 맨 왼쪽으로 보내면 가장
   작은 노드가 나옵니다.*/
  TreeNode<value_type> *iterator = FindNodePtr(x);
  while (iterator->left_ != nullptr) {
    iterator = iterator->left_;
  }
  return iterator;
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::Maximum(value_type x) {
  // Minimum과 비슷한 로직으로, 가장 큰 노드를 찾습니다.
  TreeNode<value_type> *iterator = FindNodePtr(x);
  while (iterator->right_ != nullptr) {
    iterator = iterator->right_;
  }
  return iterator;
}

template <typename value_type>
void AVLTree<value_type>::Rank(value_type x){};
void Erase(int x) {
}
template <typename value_type>
int AVLTree<value_type>::NodeHeight(TreeNode<value_type> *target_node) const {
  // Node의 Height를 nullptr인 경우에도 오류 나지 않는 방법으로 리턴합니다.
  if (target_node == nullptr) {
    return -1;
  }
  return target_node->height();
}
// protected method
template <typename value_type>
int AVLTree<value_type>::CalculateBalance(TreeNode<value_type> *target_node) {
  // 왼쪽 자식 노드의 높이 - 오른쪽 자식 노드의 높이를 통해 Balance Factor 계산
  return NodeHeight(target_node->left_) - NodeHeight(target_node->right_);
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::LLRotation(
    TreeNode<value_type> *&old_axis) {
  /*
    Left Rotation을 수행합니다.
            old                         new
            / \     Left Rotate         / \
          new  C   ------------>       A  old
          / \                             / \
         A   B                           B   C

   */
  TreeNode<value_type> *new_axis = old_axis->right_;
  old_axis->right_ = new_axis->left_;
  new_axis->left_ = old_axis;

  if (old_axis == root_) {
    root_ = new_axis;
  }
  // 축을 위 그림대로 옮겼으니, 밸런스를 다시 조정해야 합니다.
  old_axis->set_height(
      std::max(NodeHeight(old_axis->left_), NodeHeight(old_axis->right_)) + 1);
  new_axis->set_height(
      std::max(NodeHeight(new_axis->left_), NodeHeight(new_axis->right_)) + 1);
  return new_axis;
}

template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::RRRotation(
    TreeNode<value_type> *&old_axis) {
  /*
  Right Rotation
          old                         new
          / \     Right Rotate        / \
         A  new   ------------>     old  C
            / \                     / \
           B   C                   A   B

 */
  TreeNode<value_type> *new_axis = old_axis->left_;
  old_axis->left_ = new_axis->right_;
  new_axis->right_ = old_axis;
  if (old_axis == root_) {
    root_ = new_axis;
  }
  old_axis->set_height(
      std::max(NodeHeight(old_axis->left_), NodeHeight(old_axis->right_)) + 1);
  new_axis->set_height(
      std::max(NodeHeight(new_axis->left_), NodeHeight(new_axis->right_)) + 1);
  return new_axis;
}

template <typename value_type>
void AVLTree<value_type>::AdjustBalance(TreeNode<value_type> *&axis,
                                       value_type &target_key) {
  // 축과 키를 기준으로 밸런스를 조정합니다.
  int balance_factor = CalculateBalance(axis);
  if (balance_factor == -1 || balance_factor == 0 || balance_factor == 1) {
    // balance_factor가 -1,0,1이면 AVLTree의 밸런스를 만족합니다. 조정 필요 x
    return;
  }
  if (balance_factor > 1 && target_key < axis->left_->key()) {
    // 왼쪽이 높고, 새로운 노드도 왼쪽에 있다.->오른쪽 로테이션 1번으로 해결
    axis = RRRotation(axis);
  } else if (balance_factor > 1 && target_key > axis->left_->key()) { // lr상황
    // 왼쪽이 높고, 새로운 노드는 축 왼쪽에 있다.->좌회전-> 우회전
    axis->left_ = LLRotation(axis->left_);
    axis = RRRotation(axis);
  } else if (balance_factor < -1 &&
             target_key > axis->right_->key()) { // rr상황
    // 오른쪽이 높고, 새로운 노드는 축 오른쪽에 있다.->우회전 한 번
    axis = LLRotation(axis);
  } else if (balance_factor < -1 &&
             target_key < axis->right_->key()) { // rl상황
    // 오른쪽이 높고, 새로운 노드는 축 왼쪽에 있다.->우회전->좌회전
    axis->right_ = RRRotation(axis->right_);
    axis = LLRotation(axis);
  }
}

template <typename value_type>
int AVLTree<value_type>::FindDepth(value_type find_target) {
  // 타겟 노드의 Depth를 계산합니다.
  TreeNode<value_type> *iterator = root_;
  int depth_counter = 0;
  // Root(Depth:0)에서 한 번 이동할 때 마다 Depth는 1씩 깊어지는 로직입니다.
  while (iterator != nullptr && iterator->key != find_target) {
    depth_counter++;
    iterator =
        (find_target < iterator->key) ? iterator->left_ : iterator->right_;
  }
  return depth_counter;
}

template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::EraseNode(
    TreeNode<value_type> *root_node, value_type key_of_target) {
  // Implementation for Erase
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::CopyTree(
    const TreeNode<value_type> *node) {
  if (node == nullptr) {
    return nullptr;
  }
  // 복사생성자를 위해 재귀적으로 복사를 수행합니다.
  TreeNode<value_type> *new_node = new TreeNode<value_type>;
  new_node->set_key(node->key());
  new_node->left_ = CopyTree(node->left_);
  new_node->right_ = CopyTree(node->right_);
  new_node->set_height(node->height());

  return new_node;
}