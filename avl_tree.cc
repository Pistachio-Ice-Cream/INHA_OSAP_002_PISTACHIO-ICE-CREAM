/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23}.
*/
#include "avl_tree.h"

AVLTree::AVLTree() : root_(nullptr) {
}

AVLTree::~AVLTree(){
    // 소멸자 구현
}
bool AVLTree::IsEmpty() { return node_counter_ == 0; }
int AVLTree::Size() { return node_counter_; }
int AVLTree::Insert(int new_key){}
int AVLTree::Find(int x) {}
int AVLTree::Minimum(int x){
    Node *iterator = root_;
    
    while (iterator->left != nullptr)
    {
        iterator = iterator->left;
    }
    return iterator->key;
};
int AVLTree::Maximum(int x){
    Node *iterator = root_;
    while (iterator->right != nullptr)
    {
        iterator = iterator->right;
    }
    return iterator->key;
};
void AVLTree::Rank(int x){};
void Erase(int x) {}
int AVLTree::height(Node *target_node){
    if (target_node == nullptr)
        return 0;
    else
        return target_node->height;
}
/*protected members*/
Node *AVLTree::FindNodePtr(int find_target){
    Node *iterator = root_;
    while (iterator != nullptr && iterator->key != find_target)
    {
        iterator = (find_target < iterator->key) ? iterator->left : iterator->right;
    }
    return iterator;
}
int AVLTree::CalculateBalance(Node *target_node){
    return target_node->left->height - target_node->right->height;
}
Node *AVLTree::LeftRotation(Node *old_axis){ // 왼쪽 Roation을 수행합니다.
    Node *new_axis = old_axis->right;
    if (new_axis->left != nullptr)
    {
        old_axis->right = new_axis->left;
    }
    else
    {
        old_axis->right = nullptr;
    }
    new_axis->left = old_axis;
    old_axis->height =
        std::max(height(old_axis->left), height(old_axis->right)) + 1;
    new_axis->height =
        std::max(height(new_axis->left), height(new_axis->right)) + 1;
    return new_axis;
}
Node *AVLTree::RightRotation(Node *old_axis){
    Node *new_axis = old_axis->left;
    if (new_axis->right != nullptr)
    {
        old_axis->left = new_axis->right;
    }
    else
    {
        old_axis->left = nullptr;
    }
    new_axis->right = old_axis;
    old_axis->height =
        std::max(height(old_axis->left), height(old_axis->right)) + 1;
    new_axis->height =
        std::max(height(new_axis->left), height(new_axis->right)) + 1;
    return new_axis;
}

void AVLTree::AdjustBlance(Node *root, int target_key){ // root노드와 어떤 키를 기준으로 밸런스를 맞출지 정의합니다.
    int balance_factor = CalculateBalance(root);
    if (balance_factor == -1 || balance_factor == 0 ||
        balance_factor == 1) // 균형이 맞음, 밸런스 조정필요 없음
    {
        return;
    }
    if (balance_factor > 1 &&
        target_key < root->left->key) // 왼쪽이 더 큰 트리, ll의 경우
    {
        root = RightRotation(root);
    }
    else if (balance_factor > 1 && target_key > root->left->key) // lr상황
    {
        root->left = LeftRotation(root->left);
        root = RightRotation(root);
    }
    else if (balance_factor < -1 && target_key > root->right->key) // rr상황
    {
        root = LeftRotation(root);
    }
    else if (balance_factor < -1 && target_key < root->right->key) // rl상황
    {
        root->right = RightRotation(root->right);
        root = LeftRotation(root);
    }
}

Node *AVLTree::InsertNode(Node *node, int value){
    // Implementation for insertion
}

Node *AVLTree::EraseNode(Node *root_node, int key_of_target){
    // Implementation for insertion
}