#include <gtest/gtest.h>

#include <stdexcept>

#include "avl_tree.h"

class TestAVLTree : public ::testing::Test {
 protected:
  AVLTree<int>* avl_tree;

  void SetUp() {
    avl_tree = new AVLTree<int>();
  }

  void TearDown() {
    delete avl_tree;
  }

  void CreateBalancedTree() {
    avl_tree->InsertNode(avl_tree->root(), 10);
    avl_tree->InsertNode(avl_tree->root(), 6);
    avl_tree->InsertNode(avl_tree->root(), 20);
    avl_tree->InsertNode(avl_tree->root(), 2);
    avl_tree->InsertNode(avl_tree->root(), 8);
    avl_tree->InsertNode(avl_tree->root(), 12);
    avl_tree->InsertNode(avl_tree->root(), 22);
    /*    10
         /  \
        6    20
       / \   / \
      2   8 12  22   */
  }
};

TEST_F(TestAVLTree, LLrotation) {
  avl_tree->InsertNode(avl_tree->root(), 3);
  avl_tree->InsertNode(avl_tree->root(), 2);
  avl_tree->InsertNode(avl_tree->root(), 1);

  // 루트가 2인지 확인
  ASSERT_EQ(avl_tree->root()->key(), 2);
  // 루트의 왼쪽 자식이 1인지 확인
  ASSERT_EQ(avl_tree->root()->left_->key(), 1);
  // 루트의 오른쪽 자식이 3인지 확인
  ASSERT_EQ(avl_tree->root()->right_->key(), 3);
  // 트리 높이 확인
  ASSERT_EQ(avl_tree->root()->height(), 1);
}

TEST_F(TestAVLTree, LRrotation) {
  avl_tree->InsertNode(avl_tree->root(), 3);
  avl_tree->InsertNode(avl_tree->root(), 1);
  avl_tree->InsertNode(avl_tree->root(), 2);

  // 루트가 2인지 확인
  ASSERT_EQ(avl_tree->root()->key(), 2);
  // 루트의 왼쪽 자식이 1인지 확인
  ASSERT_EQ(avl_tree->root()->left_->key(), 1);
  // 루트의 오른쪽 자식이 3인지 확인
  ASSERT_EQ(avl_tree->root()->right_->key(), 3);
  // 트리 높이 확인
  ASSERT_EQ(avl_tree->root()->height(), 1);
}

TEST_F(TestAVLTree, RRrotation) {
  avl_tree->InsertNode(avl_tree->root(), 1);
  avl_tree->InsertNode(avl_tree->root(), 2);
  avl_tree->InsertNode(avl_tree->root(), 3);

  // 루트가 2인지 확인
  ASSERT_EQ(avl_tree->root()->key(), 2);
  // 루트의 왼쪽 자식이 1인지 확인
  ASSERT_EQ(avl_tree->root()->left_->key(), 1);
  // 루트의 오른쪽 자식이 3인지 확인
  ASSERT_EQ(avl_tree->root()->right_->key(), 3);
  // 트리 높이 확인
  ASSERT_EQ(avl_tree->root()->height(), 1);
}

TEST_F(TestAVLTree, RLrotation) {
  avl_tree->InsertNode(avl_tree->root(), 1);
  avl_tree->InsertNode(avl_tree->root(), 3);
  avl_tree->InsertNode(avl_tree->root(), 2);

  // 루트가 2인지 확인
  ASSERT_EQ(avl_tree->root()->key(), 2);
  // 루트의 왼쪽 자식이 1인지 확인
  ASSERT_EQ(avl_tree->root()->left_->key(), 1);
  // 루트의 오른쪽 자식이 3인지 확인
  ASSERT_EQ(avl_tree->root()->right_->key(), 3);
  // 트리 높이 확인
  ASSERT_EQ(avl_tree->root()->height(), 1);
}

TEST_F(TestAVLTree, TestEraseNode) {
  CreateBalancedTree();

  EXPECT_EQ(avl_tree->root()->key(), 10);
  // 루트 노드 삭제 테스트
  avl_tree->EraseNode(avl_tree->root(), 10);
  ASSERT_EQ(avl_tree->FindNodePtr(10), nullptr); // 노드 삭제 확인
  ASSERT_EQ(avl_tree->FindNodePtr(20)->left_, nullptr);
  ASSERT_EQ(avl_tree->root()->key(), 12); // 루트 노드 확인

  // 리프 노드 삭제
  avl_tree->EraseNode(avl_tree->root(), 22);
  ASSERT_EQ(avl_tree->FindNodePtr(22), nullptr); // 노드 삭제 확인
  ASSERT_EQ(avl_tree->FindNodePtr(20)->right_, nullptr);

  // 노드 삭제 후 자식 노드 연결 확인
  avl_tree->InsertNode(avl_tree->root(), 14);
  avl_tree->InsertNode(avl_tree->root(), 22);
  avl_tree->InsertNode(avl_tree->root(), 15);
  avl_tree->EraseNode(avl_tree->root(), 14);
  ASSERT_EQ(avl_tree->FindNodePtr(14), nullptr); // 노드 삭제 확인
  ASSERT_EQ(avl_tree->FindNodePtr(20)->left_->key(), 15); // 자식 노드 연결 확인

  // 노드 삭제 후 리밸런싱 확인
  avl_tree->InsertNode(avl_tree->root(), 24);
  avl_tree->EraseNode(avl_tree->root(), 15);
  ASSERT_EQ(avl_tree->FindNodePtr(15), nullptr); // 노드 삭제 확인
  ASSERT_EQ(avl_tree->root()->height(), 2);      // 리밸런싱 확인
  ASSERT_EQ(avl_tree->root()->right_->key(), 22);

  avl_tree->EraseNode(avl_tree->root(), 24);
  avl_tree->EraseNode(avl_tree->root(), 22);
  avl_tree->EraseNode(avl_tree->root(), 12);
  avl_tree->EraseNode(avl_tree->root(), 8);
  avl_tree->EraseNode(avl_tree->root(), 2);
  avl_tree->EraseNode(avl_tree->root(), 20);
  avl_tree->EraseNode(avl_tree->root(), 6);
  ASSERT_EQ(avl_tree->Size(), 0);
}

TEST_F(TestAVLTree, TestRank) {
  CreateBalancedTree();

  ASSERT_EQ(avl_tree->Rank(avl_tree->root(), 2), 1); // 가장 작은 키의 rank확인
  ASSERT_EQ(avl_tree->Rank(avl_tree->root(), 22),
            avl_tree->Size()); // 가장 큰 키의 rank확인

  ASSERT_EQ(avl_tree->Rank(avl_tree->root(), 10), 4);
  ASSERT_EQ(avl_tree->Rank(avl_tree->root(), 6), 2);
}

TEST_F(TestAVLTree, InsertNode) {
  avl_tree->InsertNode(avl_tree->root(), 10);
  ASSERT_EQ(avl_tree->root()->key(), 10); // 루트 노드 확인
  ASSERT_EQ(avl_tree->Size(), 1);

  avl_tree->InsertNode(avl_tree->root(), 6);
  ASSERT_EQ(avl_tree->root()->left_->key(), 6); // 왼쪽 자식 확인
  ASSERT_EQ(avl_tree->root()->height(), 1);     // 높이 확인
  ASSERT_EQ(avl_tree->Size(), 2);

  avl_tree->InsertNode(avl_tree->root(), 20);
  ASSERT_EQ(avl_tree->root()->right_->key(), 20); // 오른쪽 자식 확인
  ASSERT_EQ(avl_tree->root()->height(), 1);       // 높이 확인
  ASSERT_EQ(avl_tree->Size(), 3);

  avl_tree->InsertNode(avl_tree->root(), 2);
  ASSERT_EQ(avl_tree->root()->left_->left_->key(),
            2); // 왼쪽 자식의 왼쪽 자식 확인
  ASSERT_EQ(avl_tree->root()->height(), 2); // 높이 확인
  ASSERT_EQ(avl_tree->Size(), 4);

  avl_tree->InsertNode(avl_tree->root(), 8);
  ASSERT_EQ(avl_tree->root()->left_->right_->key(),
            8); // 왼쪽 자식의 오른쪽 자식 확인
  ASSERT_EQ(avl_tree->root()->height(), 2); // 높이 확인
  ASSERT_EQ(avl_tree->Size(), 5);

  avl_tree->InsertNode(avl_tree->root(), 12);
  ASSERT_EQ(avl_tree->root()->right_->left_->key(),
            12); // 오른쪽 자식의 왼쪽 자식 확인
  ASSERT_EQ(avl_tree->root()->height(), 2); // 높이 확인
  ASSERT_EQ(avl_tree->Size(), 6);

  avl_tree->InsertNode(avl_tree->root(), 22);
  ASSERT_EQ(avl_tree->root()->right_->right_->key(),
            22); // 오른쪽 자식의 오른쪽 자식 확인
  ASSERT_EQ(avl_tree->root()->height(), 2); // 높이 확인
  ASSERT_EQ(avl_tree->Size(), 7);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}