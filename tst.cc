#include <algorithm> // max() 함수 이용
#include <iostream>

template <typename value_type>
class treeNode {
 public:
  value_type key;
  treeNode* left = nullptr;
  treeNode* right = nullptr;
  int height = 1;
};

template <typename value_type>
class AVLTREE {
 public:
  treeNode<value_type>* root_; // 루트 노드

  // key값이 있는지 없는지 검사 있으면 pointer 값, 없으면 nullptr
  treeNode<value_type>* FindNodePtr(value_type item) {
    treeNode<value_type>* t = root_;
    while (t != nullptr && t->key != item) {
      t = (item < t->key) ? t->left : t->right;
    }
    return t;
  }

  /*새로운 key 삽입함수로 root노드 반환*/
  treeNode<value_type>* InsertNode(treeNode<value_type>* r, value_type item) {
    /*새로운 노드 삽입*/
    if (r == nullptr) {
      treeNode<value_type>* z = new treeNode<value_type>;
      z->key = item;
      r = z;
      return r;
    } else if (r->key < item) { // item이 key값보다 크다면 오른쪽으로 이동
      r->right = InsertNode(r->right, item);
    } else { // item이 key값보다 작다면 왼쪽으로 이동
      r->left = InsertNode(r->left, item);
    }
    r->height = std::max(getHeight(r->left), getHeight(r->right)) + 1;
    Balancing(r, item);
    // 새로운 노드가 추가되었으므로 재귀적으로 부모노드들 높이 1증가
    // 시켜주고 Balace Factor 측정하여 2이상이라면 재조정함수
    return r;
  }

  /* balance Factor 측정후 재조정*/
  void Balancing(treeNode<value_type>*& r, value_type item) {
    int bF = getBalanceFactor(r);

    // case 1 (left left)
    if (bF > 1 && item < r->left->key) {
      r = RotateRight(r);
    }
    // case 2 (left right)
    else if (bF > 1 && item > r->left->key) {
      r->left = RotateLeft(r->left);
      r = RotateRight(r);
    }
    // case 3 (right right)
    else if (bF < -1 && item > r->right->key) {
      r = RotateLeft(r);
    }
    // case 4 ( right left)
    else if (bF < -1 && item < r->right->key) {
      r->right = RotateRight(r->right);
      r = RotateLeft(r);
    }
  }
  /*높이 getter */
  int getHeight(treeNode<value_type>* r) {
    if (r == nullptr)
      return 0;
    else
      return r->height;
  }
  /*좌우 자식 깊이 비교하여 Balnace Factor get*/
  int getBalanceFactor(treeNode<value_type>* r) {
    return getHeight(r->left) - getHeight(r->right);
  }

  /*x를 중심으로 왼쪽으로 회전*/
  treeNode<value_type>* RotateLeft(treeNode<value_type>* x) {
    treeNode<value_type>* y = x->right;
    x->right = y->left;
    y->left = x;

    // 위치가 바뀌었으므로 높이 재조정
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
  }
  /*y를 중심으로 오른쪽으로 회전*/
  treeNode<value_type>* RotateRight(treeNode<value_type>* y) {
    treeNode<value_type>* x = y->left;
    y->left = x->right;
    x->right = y;

    // 위치가 바뀌었으므로 높이 재조정
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
  }
  int FindDepth(value_type find_target) {
    treeNode<value_type>* iterator = root_;
    int depth_counter = 0;
    while (iterator != nullptr && iterator->key != find_target) {
      depth_counter++;
      iterator =
          (find_target < iterator->key) ? iterator->left : iterator->right;
    }
    return depth_counter;
  };

  /*show tree*/
  void print_helper(treeNode<value_type>* root, std::string indent, bool last) {
    // print the tree structure on the screen
    if (root != nullptr) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "     ";
      } else {
        std::cout << "L----";
        indent += "|    ";
      }

      int height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
      std::cout << root->key << " (" << height << ")" << std::endl;
      print_helper(root->left, indent, false);
      print_helper(root->right, indent, true);
    }
  }

 public:
  AVLTREE() {
    this->root_ = nullptr;
  }
  // 최솟값 찾기
  treeNode<value_type>* Minimum(value_type x) {
    treeNode<value_type>* iterator = FindNodePtr(x);
    while (iterator->left != nullptr) {
      iterator = iterator->left;
    }
    return iterator;
  }
  // 최댓값 찾기
  treeNode<value_type>* Maximum(value_type x) {
    treeNode<value_type>* iterator = FindNodePtr(x);
    while (iterator->right != nullptr) {
      iterator = iterator->right;
    }
    return iterator;
  }
  int Size() {
    return node_counter;
  }
  bool IsEmpty() {
    return node_counter == 0;
  }
  int node_counter = 0;
};

int main() {
  int T;
  std::cin >> T;
  while (T--) {
    int Q;
    std::cin >> Q;
    AVLTREE<int> s;
    while (Q--) {
      std::string cmd;
      std::cin >> cmd;
      if (cmd == "minimum") {
        int x;
        std::cin >> x;
        std::cout << s.Minimum(x)->key << " ";
        std::cout << s.FindDepth(s.Minimum(x)->key) << "\n";
      } else if (cmd == "maximum") {
        int x;
        std::cin >> x;
        std::cout << s.Maximum(x)->key;
        std::cout << s.FindDepth(s.Maximum(x)->key);
      } else if (cmd == "empty") {
        std::cout << s.IsEmpty() << "\n";
      } else if (cmd == "size") {
        std::cout << s.Size() << "\n";
      } else if (cmd == "find") {
        int x;
        std::cin >> x;
        if (s.FindNodePtr(x) != nullptr) {
          std::cout << s.FindDepth(s.FindNodePtr(x)->key);
        } else {
          std::cout << "0";
        }
      } else if (cmd == "insert") {
        int x;
        std::cin >> x;
        s.InsertNode(s.root_, x);
        std::cout << s.FindDepth(s.FindNodePtr(x)->key);
      } else {
        s.print_helper(s.root_, "", true);
      }
    }
  }
}