#include <iostream>
#include <queue>
#include <stack>

struct Node {
  int val_;
  Node *left_;
  Node *right_;

  explicit Node(int val);
};

Node::Node(int val)
    : val_(val), left_(nullptr), right_(nullptr) {}

class Tree {
 private:
  Node *root;

 public:
  explicit Tree();

  ~Tree();

  void Insert(int val);

  std::stack<Node *> postOrder();

  int FindMinDist();
};

Tree::Tree() : root(nullptr) {}

std::stack<Node *> Tree::postOrder() {
  std::stack<Node *> ans;
  std::stack<Node *> tmp;
  Node *curRoot = root;
  tmp.push(curRoot);
  while (!tmp.empty()) {
    Node *topElem = tmp.top();
    if (topElem->right_ == nullptr && topElem->left_ == nullptr) {
      ans.push(topElem);
      curRoot = topElem;
      tmp.pop();
    } else {
      if (topElem->right_ == curRoot || topElem->left_ == curRoot) {
        curRoot = topElem;
        ans.push(topElem);
        tmp.pop();
        continue;
      }
      if (topElem->left_ != nullptr) {
        tmp.push(topElem->left_);
      }
      if (topElem->right_ != nullptr) {
        tmp.push(topElem->right_);
      }
    }
  }
  return ans;
}

Tree::~Tree() {
  std::stack<Node *> s = postOrder();
  while (!s.empty()) {
    Node *toDelete = s.top();
    s.pop();
    delete toDelete;
  }
}

void Tree::Insert(int val) {
  if (!root) {
    root = new Node(val);
    return;
  }
  Node *tmp = root;
  while (tmp != nullptr) {
    if (val > tmp->val_) {
      if (tmp->right_ == nullptr) {
        tmp->right_ = new Node(val);
        return;
      } else {
        tmp = tmp->right_;
      }
    } else {
      if (tmp->left_ == nullptr) {
        tmp->left_ = new Node(val);
        return;
      } else {
        tmp = tmp->left_;
      }
    }
  }
}

int Tree::FindMinDist() {
  if (!root){
    return 0;
  }
  std::queue<Node *> q;
  q.push(root);
  int res = 0;
  while (!q.empty()) {
    size_t lenQ = q.size();
    res++;
    for (size_t i = 0; i < lenQ; i++) {
      Node *curNode = q.front();
      q.pop();
      if ((curNode->left_ == nullptr) && (curNode->right_ == nullptr)) {
        return res;
      }
      if (curNode->left_ != nullptr) {
        q.push(curNode->left_);
      }
      if (curNode->right_ != nullptr) {
        q.push(curNode->right_);
      }
    }
  }
  return res;
}

int main() {
  int val = 0;
  Tree tree = Tree();
  while (std::cin >> val) {
    tree.Insert(val);
  }
  std::cout << tree.FindMinDist() << std::endl;
  return 0;
}