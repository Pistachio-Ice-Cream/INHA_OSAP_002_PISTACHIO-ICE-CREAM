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

  // ��Ʈ�� 2���� Ȯ��
  ASSERT_EQ(avl_tree->root()->key(), 2);
  // ��Ʈ�� ���� �ڽ��� 1���� Ȯ��
  ASSERT_EQ(avl_tree->root()->left_->key(), 1);
  // ��Ʈ�� ������ �ڽ��� 3���� Ȯ��
  ASSERT_EQ(avl_tree->root()->right_->key(), 3);
  // Ʈ�� ���� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 1);
}

TEST_F(TestAVLTree, LRrotation) {
  avl_tree->InsertNode(avl_tree->root(), 3);
  avl_tree->InsertNode(avl_tree->root(), 1);
  avl_tree->InsertNode(avl_tree->root(), 2);

  // ��Ʈ�� 2���� Ȯ��
  ASSERT_EQ(avl_tree->root()->key(), 2);
  // ��Ʈ�� ���� �ڽ��� 1���� Ȯ��
  ASSERT_EQ(avl_tree->root()->left_->key(), 1);
  // ��Ʈ�� ������ �ڽ��� 3���� Ȯ��
  ASSERT_EQ(avl_tree->root()->right_->key(), 3);
  // Ʈ�� ���� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 1);
}

TEST_F(TestAVLTree, RRrotation) {
  avl_tree->InsertNode(avl_tree->root(), 1);
  avl_tree->InsertNode(avl_tree->root(), 2);
  avl_tree->InsertNode(avl_tree->root(), 3);

  // ��Ʈ�� 2���� Ȯ��
  ASSERT_EQ(avl_tree->root()->key(), 2);
  // ��Ʈ�� ���� �ڽ��� 1���� Ȯ��
  ASSERT_EQ(avl_tree->root()->left_->key(), 1);
  // ��Ʈ�� ������ �ڽ��� 3���� Ȯ��
  ASSERT_EQ(avl_tree->root()->right_->key(), 3);
  // Ʈ�� ���� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 1);
}

TEST_F(TestAVLTree, RLrotation) {
  avl_tree->InsertNode(avl_tree->root(), 1);
  avl_tree->InsertNode(avl_tree->root(), 3);
  avl_tree->InsertNode(avl_tree->root(), 2);

  // ��Ʈ�� 2���� Ȯ��
  ASSERT_EQ(avl_tree->root()->key(), 2);
  // ��Ʈ�� ���� �ڽ��� 1���� Ȯ��
  ASSERT_EQ(avl_tree->root()->left_->key(), 1);
  // ��Ʈ�� ������ �ڽ��� 3���� Ȯ��
  ASSERT_EQ(avl_tree->root()->right_->key(), 3);
  // Ʈ�� ���� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 1);
}

TEST_F(TestAVLTree, TestEraseNode) {
  CreateBalancedTree();

  EXPECT_EQ(avl_tree->root()->key(), 10);
  // ��Ʈ ��� ���� �׽�Ʈ
  avl_tree->EraseNode(avl_tree->root(), 10);
  ASSERT_EQ(avl_tree->FindNodePtr(10), nullptr); // ��� ���� Ȯ��
  ASSERT_EQ(avl_tree->FindNodePtr(20)->left_, nullptr);
  ASSERT_EQ(avl_tree->root()->key(), 12); // ��Ʈ ��� Ȯ��

  // ���� ��� ����
  avl_tree->EraseNode(avl_tree->root(), 22);
  ASSERT_EQ(avl_tree->FindNodePtr(22), nullptr); // ��� ���� Ȯ��
  ASSERT_EQ(avl_tree->FindNodePtr(20)->right_, nullptr);

  // ��� ���� �� �ڽ� ��� ���� Ȯ��
  avl_tree->InsertNode(avl_tree->root(), 14);
  avl_tree->InsertNode(avl_tree->root(), 22);
  avl_tree->InsertNode(avl_tree->root(), 15);
  avl_tree->EraseNode(avl_tree->root(), 14);
  ASSERT_EQ(avl_tree->FindNodePtr(14), nullptr); // ��� ���� Ȯ��
  ASSERT_EQ(avl_tree->FindNodePtr(20)->left_->key(), 15); // �ڽ� ��� ���� Ȯ��

  // ��� ���� �� ���뷱�� Ȯ��
  avl_tree->InsertNode(avl_tree->root(), 24);
  avl_tree->EraseNode(avl_tree->root(), 15);
  ASSERT_EQ(avl_tree->FindNodePtr(15), nullptr); // ��� ���� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 2);      // ���뷱�� Ȯ��
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

  ASSERT_EQ(avl_tree->Rank(avl_tree->root(), 2), 1); // ���� ���� Ű�� rankȮ��
  ASSERT_EQ(avl_tree->Rank(avl_tree->root(), 22),
            avl_tree->Size()); // ���� ū Ű�� rankȮ��

  ASSERT_EQ(avl_tree->Rank(avl_tree->root(), 10), 4);
  ASSERT_EQ(avl_tree->Rank(avl_tree->root(), 6), 2);
}

TEST_F(TestAVLTree, InsertNode) {
  avl_tree->InsertNode(avl_tree->root(), 10);
  ASSERT_EQ(avl_tree->root()->key(), 10); // ��Ʈ ��� Ȯ��
  ASSERT_EQ(avl_tree->Size(), 1);

  avl_tree->InsertNode(avl_tree->root(), 6);
  ASSERT_EQ(avl_tree->root()->left_->key(), 6); // ���� �ڽ� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 1);     // ���� Ȯ��
  ASSERT_EQ(avl_tree->Size(), 2);

  avl_tree->InsertNode(avl_tree->root(), 20);
  ASSERT_EQ(avl_tree->root()->right_->key(), 20); // ������ �ڽ� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 1); // ���� Ȯ��
  ASSERT_EQ(avl_tree->Size(), 3);

  avl_tree->InsertNode(avl_tree->root(), 2);
  ASSERT_EQ(avl_tree->root()->left_->left_->key(),
            2); // ���� �ڽ��� ���� �ڽ� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 2); // ���� Ȯ��
  ASSERT_EQ(avl_tree->Size(), 4);

  avl_tree->InsertNode(avl_tree->root(), 8);
  ASSERT_EQ(avl_tree->root()->left_->right_->key(),
            8); // ���� �ڽ��� ������ �ڽ� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 2); // ���� Ȯ��
  ASSERT_EQ(avl_tree->Size(), 5);

  avl_tree->InsertNode(avl_tree->root(), 12);
  ASSERT_EQ(avl_tree->root()->right_->left_->key(),
            12); // ������ �ڽ��� ���� �ڽ� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 2); // ���� Ȯ��
  ASSERT_EQ(avl_tree->Size(), 6);

  avl_tree->InsertNode(avl_tree->root(), 22);
  ASSERT_EQ(avl_tree->root()->right_->right_->key(),
            22); // ������ �ڽ��� ������ �ڽ� Ȯ��
  ASSERT_EQ(avl_tree->root()->height(), 2); // ���� Ȯ��
  ASSERT_EQ(avl_tree->Size(), 7);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}