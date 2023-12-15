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

TEST(NodeTests, TestKey) {
  Node<int> node;
  node->set_key(1);
  ASSERT_EQ(1, node->key());
}

class TreeNodeTest : public ::testing::Test {
 protected:
  TreeNode<int>* node;

  void SetUp() override {
    node = new TreeNode<int>();
  }

  void TearDown() override {
    delete node;
  }
};

TEST_F(TreeNodeTest, CheckHeight) {
  node->set_height(5);
  EXPECT_EQ(node->height(), 5);
}

TEST_F(TreeNodeTest, CheckSize) {
  node->set_size(10);
  EXPECT_EQ(node->size(), 10);
}

TEST_F(TreeNodeTest, CheckLeftIsNull) {
  EXPECT_TRUE(node->LeftIsNull());
  node->left_ = new TreeNode<int>();
  EXPECT_FALSE(node->LeftIsNull());
  delete node->left_;
}

TEST_F(TreeNodeTest, CheckRightIsNull) {
  EXPECT_TRUE(node->RightIsNull());
  node->right_ = new TreeNode<int>();
  EXPECT_FALSE(node->RightIsNull());
  delete node->right_;
}

TEST_F(TreeNodeTest, CheckNoChild) {
  EXPECT_TRUE(node->NoChild());
  node->left_ = new TreeNode<int>();
  EXPECT_FALSE(node->NoChild());
  delete node->left_;
  node->right_ = new TreeNode<int>();
  EXPECT_FALSE(node->NoChild());
  delete node->right_;
}

class AVLTreeTest : public ::testing::Test {
 protected:
  AVLTree<int>* tree;

  void SetUp() override {
    tree = new AVLTree<int>();
    SetUpTestCase();
  }

  void TearDown() override {
    delete tree;
  }

  void SetUpTestCase() {
    tree.InsertNode(tree->root(), 1);
    tree.InsertNode(tree->root(), 2);
    tree.InsertNode(tree->root(), 3);
    tree.InsertNode(tree->root(), 4);
    tree.InsertNode(tree->root(), 5);
    tree.InsertNode(tree->root(), 6);
    /*
            3
          /   \
        2      5
       /      / \
      1      4   6
    */
  }
};

TEST_F(AVLTreeTest, TestRoot) {
  EXPECT_TRUE(tree->root() != nullptr);
}

TEST_F(AVLTreeTest, TestCopyConstructor) {
  AVLTree<int> copy_tree(*tree);
  EXPECT_TRUE(copy_tree->root() != nullptr);
}

TEST_F(AVLTreeTest, TestIsEmpty) {
  EXPECT_FALSE(tree.IsEmpty());
}

TEST_F(AVLTreeTest, TestSize) {
  EXPECT_EQ(tree.Size(), 6);
}

TEST_F(AVLTreeTest, TestFindNodePtr) {
  ASSERT_EQ(tree.FindNodePtr(1)->key(), 1);
  ASSERT_EQ(tree.FindNodePtr(2)->key(), 2);
  ASSERT_EQ(tree.FindNodePtr(3)->key(), 3);
  ASSERT_EQ(tree.FindNodePtr(4)->key(), 4);
  ASSERT_EQ(tree.FindNodePtr(5)->key(), 5);
  ASSERT_EQ(tree.FindNodePtr(6)->key(), 6);
}

TEST_F(AVLTreeTest, TestMinimum) {
  ASSERT_EQ(tree.Minimum()->key(), 1);
}

TEST_F(AVLTreeTest, TestMaximum) {
  ASSERT_EQ(tree.Maximum()->key(), 6);
}

TEST_F(AVLTreeTest, TestRank) {
  ASSERT_EQ(tree.Rank(tree->root(), 1), 1);
  ASSERT_EQ(tree.Rank(tree->root(), 2), 2);
  ASSERT_EQ(tree.Rank(tree->root(), 3), 3);
  ASSERT_EQ(tree.Rank(tree->root(), 4), 4);
  ASSERT_EQ(tree.Rank(tree->root(), 5), 5);
  ASSERT_EQ(tree.Rank(tree->root(), 6), 6);
}

TEST_F(AVLTreeTest, TestNodeHeight) {
  ASSERT_EQ(tree.NodeHeight(tree->root()), 2);
  ASSERT_EQ(tree.NodeHeight(tree->root()->left_), 1);
  ASSERT_EQ(tree.NodeHeight(tree->root()->right_), 1);
  ASSERT_EQ(tree.NodeHeight(tree->root()->right_->right_), 0);
}

TEST_F(AVLTreeTest, TestFindDepth) {
  ASSERT_EQ(tree.FindDepth(3), 1);
  ASSERT_EQ(tree.FindDepth(2), 2);
  ASSERT_EQ(tree.FindDepth(5), 2);
  ASSERT_EQ(tree.FindDepth(1), 3);
  ASSERT_EQ(tree.FindDepth(4), 3);
  ASSERT_EQ(tree.FindDepth(6), 3);
}

TEST_F(AVLTreeTest, TestCalculateHeight) {
  ASSERT_EQ(tree.CalculateHeight(tree->root()), 2);
  ASSERT_EQ(tree.CalculateHeight(tree->root()->left_), 1);
  ASSERT_EQ(tree.CalculateHeight(tree->root()->right_), 1);
  ASSERT_EQ(tree.CalculateHeight(tree->root()->right_->right_), 0);
}

TEST_F(AVLTreeTest, TestCalculateSize) {
  ASSERT_EQ(tree.CalculateSize(tree->root()), 6);
  ASSERT_EQ(tree.CalculateSize(tree->root()->left_), 2);
  ASSERT_EQ(tree.CalculateSize(tree->root()->right_), 3);
  ASSERT_EQ(tree.CalculateSize(tree->root()->right_->right_), 1);
}

TEST_F(AVLTreeTest, TestCalculateBalance) {
  ASSERT_EQ(tree.CalculateBalance(tree->root()), 0);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}