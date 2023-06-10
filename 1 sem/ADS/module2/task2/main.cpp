// 2 задача 4 вариант
// Окутин Денис

//Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
//Требуется построить бинарное дерево поиска, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
//Выведите элементы в порядке level-order (по слоям, “в ширину”).


#include <iostream>
#include <queue>
#include <stack>

class MyComparator {
public:
    bool operator()(const int l, const int r) { return l > r; }
};

struct Node {
    int val_;
    Node *left_;
    Node *right_;

    explicit Node(int val);
};

Node::Node(int val) : val_(val), left_(nullptr), right_(nullptr) {}

template<typename Comparator>
class Tree {
private:
    Node *root;
    Comparator cmp_;

public:
    explicit Tree(Comparator cmp);

    ~Tree();

    void Insert(int val);

    std::stack<Node *> postOrder();

    void printLevelOrder();
};

template<typename Comparator>
Tree<Comparator>::Tree(Comparator cmp) : cmp_(cmp), root(nullptr) {}

template<typename Comparator>
std::stack<Node *> Tree<Comparator>::postOrder() {
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

template<typename Comparator>
Tree<Comparator>::~Tree() {
    std::stack<Node *> s = postOrder();
    while (!s.empty()) {
        Node *toDelete = s.top();
        s.pop();
        delete toDelete;
    }
}

template<typename Comparator>
void Tree<Comparator>::Insert(int val) {
    if (!root) {
        root = new Node(val);
        return;
    }
    Node *tmp = root;
    while (tmp != nullptr) {
        if (cmp_(val, tmp->val_)) {
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

template<typename Comparator>
void Tree<Comparator>::printLevelOrder() {
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node *curNode = q.front();
        q.pop();
        std::cout << curNode->val_ << " ";
        if (curNode->left_ != nullptr) {
            q.push(curNode->left_);
        }
        if (curNode->right_ != nullptr) {
            q.push(curNode->right_);
        }
    }
}

int main() {
    int N = 0;
    std::cin >> N;
    int val;
    Tree<MyComparator> root{MyComparator()};
    for (int i = 0; i < N; i++) {
        std::cin >> val;
        root.Insert(val);
    }
    root.printLevelOrder();
    return 0;
}