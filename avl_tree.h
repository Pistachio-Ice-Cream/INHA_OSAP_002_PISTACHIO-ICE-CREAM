/*
Copyright (c) 2023 Pistachio-Ice-Cream.
Distributed under the MIT License (http://opensource.org/licenses/MIT).
Created At: 2023-11-12, Created By: {rla1wo23}.
*/
#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <algorithm>
#include <iostream>
class Node {
private:
    int key;
    int height = 0;
    Node *left = nullptr;
    Node *right = nullptr;
    friend class AVLTree;
};
class AVLTree {
public:        // 자식 클래스에서 public함수를 통해서만 AVLTree에 접근할 수 있게끔 합니다.
    AVLTree(); // Rule of Three를 만족하게끔 1)복사생성자 2)소멸자를 적절히 추가해야 합니다.
    ~AVLTree();
    bool IsEmpty();
    int Size();
    int Insert(int new_key);
    // 최솟값 찾기
    int Find(int x);
    int Minimum(int x);
    int Maximum(int x);
    void Rank(int x);
    void Erase(int x);
    int height(Node *target_node); // nullptr의 height를 호출할 수도 있는 경우가 발생할 수 있으므로, 멤버에 직접 접근하지 않고 함수로 접근하는게 안전합니다.
    /*직접 데이터 멤버들을 조작할 수 있는 위험한 함수들입니다.*/
protected:                              // protected부분은 자식 클래스에서 직접 호출해서 사용할 수 없으므로 아래 함수들은 public함수를 통해서 접근해서 도구적으로 사용됩니다.
    Node *FindNodePtr(int find_target); // 찾고자 하는 노드의 포인터를 반환. input:key, output: 해당 key를 가진 노드의 포인터
    int CalculateBalance(Node *target_node);
    Node *LeftRotation(Node *old_axis); // 왼쪽 Roation을 수행합니다.
    Node *RightRotation(Node *old_axis);
    void AdjustBlance(Node *root, int target_key); // root노드와 어떤 키를 기준으로 밸런스를 맞출지 정의합니다.
    Node *InsertNode(Node *iterator, int key_of_new_node); // 새로운 노드 생성 삽입, 밸런싱
    Node *EraseNode(Node *root_node, int key_of_target); // 노드를 삭제합니다.
    int FindDepth(int find_target); // 해당 key를 가진 노드의 depth 리턴

protected:
    int node_counter_ = 0;
    Node *root_;
};
#endif // AVL_TREE_H