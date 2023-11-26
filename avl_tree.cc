/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23, rla1wo23@gmail.com}.
*/
#include "avl_tree.h"
template <typename value_type>
value_type Node<value_type>::key() const {
  return key_;
}

template <typename value_type>
void Node<value_type>::set_key(value_type new_key) {
  key_ = new_key;
}
template <typename value_type>
int TreeNode<value_type>::height() const {
  return height_;
}
template <typename value_type>
void TreeNode<value_type>::set_height(int new_height) {
  height_ = new_height;
}
template <typename value_type>
void TreeNode<value_type>::Balancing() {
  int height_of_left = 0, height_of_right = 0;
  bool is_root = true;
  if (left_ != nullptr) {
    height_of_left = left_->height();
    is_root = false;
  }
  if (right_ != nullptr) {
    height_of_right = right_->height();
    is_root = false;
  }
  if (is_root == true) {
    set_height(0);
  } else {
    set_height(std::max(height_of_left, height_of_right) + 1);
  }
}
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
AVLTree<value_type>::~AVLTree() { // 소멸자 구현
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
  if (IsEmpty()) {
    root_ = new TreeNode<value_type>;
    root_->set_key(key_of_new_node);
    this->node_counter_++;
    return root_;
  }
  if (iterator == nullptr) {
    TreeNode<value_type> *new_node = new TreeNode<value_type>;
    this->node_counter_++;
    iterator = new_node; // 추가된 부분
    new_node->set_key(key_of_new_node);
    return new_node;
  } else if (iterator->key() < key_of_new_node) {
    iterator->right_ = InsertNode(iterator->right_, key_of_new_node);
    // iterator->right->parent = iterator;
  } else {
    iterator->left_ = InsertNode(iterator->left_, key_of_new_node);
    // iterator->left->parent = iterator;
  }
  iterator->set_height(
      (std::max(NodeHeight(iterator->left_), NodeHeight(iterator->right_))) +
      1);
  AdjustBlance(iterator, key_of_new_node);
  return iterator;
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::FindNodePtr(value_type find_target) {
  TreeNode<value_type> *iterator = root_;
  while (iterator != nullptr && iterator->key() != find_target) {
    iterator =
        (find_target < iterator->key()) ? iterator->left_ : iterator->right_;
  }
  if (iterator == nullptr) {
    return nullptr;
  } else {
    return iterator;
  }
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::Minimum(value_type x) {
  TreeNode<value_type> *iterator = FindNodePtr(x);
  while (iterator->left_ != nullptr) {
    iterator = iterator->left_;
  }
  return iterator;
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::Maximum(value_type x) {
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
int AVLTree<value_type>::height(TreeNode<value_type> *target_node) {
  if (target_node == nullptr)
    return 0;
  else
    return target_node->height_;
}
/*protected members*/

template <typename value_type>
int AVLTree<value_type>::CalculateBalance(TreeNode<value_type> *target_node) {
  return target_node->left_->height_ - target_node->right_->height_;
}
template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::LLRotation(
    TreeNode<value_type> *old_axis) { // 왼쪽 Roation을 수행합니다.
  TreeNode<value_type> *new_axis = old_axis->right_;
  if (new_axis->left_ != nullptr) {
    old_axis->right_ = new_axis->left_;
  } else {
    old_axis->right_ = nullptr;
  }
  new_axis->left_ = old_axis;
  old_axis->height_ =
      std::max(height(old_axis->left_), height(old_axis->right_)) + 1;
  new_axis->height_ =
      std::max(height(new_axis->left_), height(new_axis->right_)) + 1;
  return new_axis;
}

template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::RRRotation(
    TreeNode<value_type> *old_axis) {
  TreeNode<value_type> *new_axis = old_axis->left_;
  if (new_axis->right_ != nullptr) {
    old_axis->left_ = new_axis->right_;
  } else {
    old_axis->left_ = nullptr;
  }
  new_axis->right_ = old_axis;
  old_axis->height_ =
      std::max(height(old_axis->left_), height(old_axis->right_)) + 1;
  new_axis->height_ =
      std::max(height(new_axis->left_), height(new_axis->right_)) + 1;
  return new_axis;
}

template <typename value_type>
void AVLTree<value_type>::AdjustBlance(
    TreeNode<value_type> *root,
    value_type target_key) { // root노드와 어떤 키를 기준으로
  // 밸런스를 맞출지 정의합니다.
  int balance_factor = CalculateBalance(root);
  if (balance_factor == -1 || balance_factor == 0 ||
      balance_factor == 1) { // 균형이 맞음, 밸런스 조정필요 없음
    return;
  }
  if (balance_factor > 1 &&
      target_key < root->left_->key) { // 왼쪽이 더 큰 트리, ll의 경우
    root = RRRotation(root);
  } else if (balance_factor > 1 && target_key > root->left_->key) { // lr상황
    root->left_ = LLRotation(root->left_);
    root = RRRotation(root);
  } else if (balance_factor < -1 && target_key > root->right_->key) { // rr상황
    root = LLRotation(root);
  } else if (balance_factor < -1 && target_key < root->right_->key) { // rl상황
    root->right_ = RRRotation(root->right_);
    root = LLRotation(root);
  }
}

template <typename value_type>
TreeNode<value_type> *AVLTree<value_type>::InsertNode(
    TreeNode<value_type> *iterator,
    value_type key_of_new_node) { // 새로운 노드 삽입
  if (iterator == nullptr) { // 현재 iterator위치가 비어있으면 삽입
    TreeNode<value_type> *new_node = new treeNode;
    this->node_counter_++;
    new_node->key = key_of_new_node;
    return new_node;
  } else if (iterator->key <
             key_of_new_node) { // 새로운 key값이 현재 iterator의 key값보다
    // 크면 오른쪽 이동
    iterator->right_ = InsertNode(iterator->right_, key_of_new_node);
  } else { // 새로운 key값이 현재 iterator의 key값보다 크면 왼쪽 이동
    iterator->left_ = InsertNode(iterator->left_, key_of_new_node);
  }
  iterator->height_ =
      std::max(height(iterator->left_),
               height(iterator->right_));  // iterator의 높이 갱신
  AdjustBlance(iterator, key_of_new_node); // iterator기준 밸런싱
  return iterator;
}

template <typename value_type>
int AVLTree<value_type>::FindDepth(value_type find_target) {
  TreeNode<value_type> *iterator = root_;
  int depth_counter = 0;
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