/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23}.
*/
#include "avl_tree.h"

template <typename value_type>
AVLTree<value_type>::AVLTree() : root_(nullptr) {
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
int AVLTree<value_type>::Minimum(value_type x) {
  treeNode<value_type> *iterator = FindNodePtr(x);
  while (iterator->left != nullptr) {
    iterator = iterator->left;
  }
  return iterator->key;
}
template <typename value_type>
int AVLTree<value_type>::Maximum(value_type x) {
  treeNode<value_type> *iterator = FindNodePtr(x);
  while (iterator->right != nullptr) {
    iterator = iterator->right;
  }
  return iterator->key;
}

template <typename value_type>
void AVLTree<value_type>::Rank(value_type x){};
void Erase(int x) {
}
template <typename value_type>
int AVLTree<value_type>::height(treeNode<value_type> *target_node) {
  if (target_node == nullptr)
    return 0;
  else
    return target_node->height;
}
/*protected members*/
template <typename value_type>
treeNode<value_type> *AVLTree<value_type>::FindNodePtr(value_type find_target) {
  treeNode<value_type> *iterator = root_;
  while (iterator != nullptr && iterator->key != find_target) {
    iterator = (find_target < iterator->key) ? iterator->left : iterator->right;
  }
  return iterator;
}

template <typename value_type>
int AVLTree<value_type>::CalculateBalance(treeNode<value_type> *target_node) {
  return target_node->left->height - target_node->right->height;
}
template <typename value_type>
treeNode<value_type> *AVLTree<value_type>::LeftRotation(
    treeNode<value_type> *old_axis) { // 왼쪽 Roation을 수행합니다.
  treeNode<value_type> *new_axis = old_axis->right;
  if (new_axis->left != nullptr) {
    old_axis->right = new_axis->left;
  } else {
    old_axis->right = nullptr;
  }
  new_axis->left = old_axis;
  old_axis->height =
      std::max(height(old_axis->left), height(old_axis->right)) + 1;
  new_axis->height =
      std::max(height(new_axis->left), height(new_axis->right)) + 1;
  return new_axis;
}

template <typename value_type>
treeNode<value_type> *AVLTree<value_type>::RightRotation(
    treeNode<value_type> *old_axis) {
  treeNode<value_type> *new_axis = old_axis->left;
  if (new_axis->right != nullptr) {
    old_axis->left = new_axis->right;
  } else {
    old_axis->left = nullptr;
  }
  new_axis->right = old_axis;
  old_axis->height =
      std::max(height(old_axis->left), height(old_axis->right)) + 1;
  new_axis->height =
      std::max(height(new_axis->left), height(new_axis->right)) + 1;
  return new_axis;
}

template <typename value_type>
void AVLTree<value_type>::AdjustBlance(
    treeNode<value_type> *root,
    value_type target_key) { // root노드와 어떤 키를 기준으로
  // 밸런스를 맞출지 정의합니다.
  int balance_factor = CalculateBalance(root);
  if (balance_factor == -1 || balance_factor == 0 ||
      balance_factor == 1) { // 균형이 맞음, 밸런스 조정필요 없음
    return;
  }
  if (balance_factor > 1 &&
      target_key < root->left->key) { // 왼쪽이 더 큰 트리, ll의 경우
    root = RightRotation(root);
  } else if (balance_factor > 1 && target_key > root->left->key) { // lr상황
    root->left = LeftRotation(root->left);
    root = RightRotation(root);
  } else if (balance_factor < -1 && target_key > root->right->key) { // rr상황
    root = LeftRotation(root);
  } else if (balance_factor < -1 && target_key < root->right->key) { // rl상황
    root->right = RightRotation(root->right);
    root = LeftRotation(root);
  }
}

template <typename value_type>
treeNode<value_type> *AVLTree<value_type>::InsertNode(
    treeNode<value_type> *iterator,
    value_type key_of_new_node) { // 새로운 노드 삽입
  if (iterator == nullptr) { // 현재 iterator위치가 비어있으면 삽입
    treeNode<value_type> *new_node = new treeNode;
    this->node_counter_++;
    new_node->key = key_of_new_node;
    return new_node;
  } else if (iterator->key <
             key_of_new_node) { // 새로운 key값이 현재 iterator의 key값보다
    // 크면 오른쪽 이동
    iterator->right = InsertNode(iterator->right, key_of_new_node);
  } else { // 새로운 key값이 현재 iterator의 key값보다 크면 왼쪽 이동
    iterator->left = InsertNode(iterator->left, key_of_new_node);
  }
  iterator->height = std::max(height(iterator->left),
                              height(iterator->right)); // iterator의 높이 갱신
  AdjustBlance(iterator, key_of_new_node); // iterator기준 밸런싱
  return iterator;
}

template <typename value_type>
int AVLTree<value_type>::FindDepth(value_type find_target) {
  treeNode<value_type> *iterator = root_;
  int depth_counter = 0;
  while (iterator != nullptr && iterator->key != find_target) {
    depth_counter++;
    iterator = (find_target < iterator->key) ? iterator->left : iterator->right;
  }
  return depth_counter;
}

template <typename value_type>
treeNode<value_type> *AVLTree<value_type>::EraseNode(
    treeNode<value_type> *root_node, value_type key_of_target) {
  // Implementation for Erase
}