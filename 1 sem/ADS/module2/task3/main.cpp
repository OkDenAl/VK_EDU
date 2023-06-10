// Задача 3 Окутин Денис

//Постройте B-дерево минимального порядка t и выведите его по слоям.
//В качестве ключа используются числа, лежащие в диапазоне [0..232-1]
//Требования:
//
//B-дерево должно быть реализовано в виде шаблонного класса.
//Решение должно поддерживать передачу функции сравнения снаружи.

#include <iostream>
#include <vector>
#include <queue>

template<typename T>
class MyComparator {
public:
    bool operator()(const T &l, const T &r) { return l < r; }
};

template<typename T, typename Comparator>
class BTree {
public:
    struct Node {
        explicit Node(bool leaf) : leaf(leaf) {}

        ~Node() {
            for (Node *child: children) {
                delete child;
            }
        }

        bool leaf;
        std::vector<T> keys;
        std::vector<Node *> children;
    };

    explicit BTree(size_t min_degree, Comparator cmp) : t(min_degree), cmp(cmp), root(nullptr) {}

    ~BTree() {
        delete root;
    }

    void Insert(const T &key) {
        if (!root) root = new Node(true);

        if (isNodeFull(root)) {
            Node *newRoot = new Node(false);
            newRoot->children.push_back(root);
            root = newRoot;
            splitChild(root, root->children[0], 0);
        }

        insertNonFull(root, key);
    }

    void BFSPrint() {
        BFSPrintInternal(root);
    }

private:
    void BFSPrintInternal(Node *node) {
        std::queue<std::pair<Node *, int>> q;
        q.push(std::pair<Node *, int>(node, 0));
        int prevLevel = 0;
        while (!q.empty()) {
            Node *curNode = q.front().first;
            int curLevel = q.front().second;
            if (prevLevel != curLevel) {
                std::cout << std::endl;
            }
            q.pop();
            for (auto it = curNode->keys.begin(); it != curNode->keys.end(); it++) {
                std::cout << (*it) << " ";
            }
            for (auto child: curNode->children) {
                q.push(std::pair<Node *, int>(child, curLevel + 1));
            }
            prevLevel = curLevel;
        }
    }

    bool isNodeFull(Node *node) { return node->keys.size() == 2 * t - 1; }

    void splitChild(Node *curRoot, Node *node, size_t index) {
        Node *newChild = new Node(node->leaf);
        newChild->keys = std::vector<T>(t - 1);
        for (size_t i = 0; i < t - 1; i++) {
            newChild->keys[i] = node->keys[i + t];
        }
        if (node->leaf == false) {
            newChild->children = std::vector<Node *>(t);
            for (size_t i = 0; i < t; i++) {
                newChild->children[i] = node->children[i + t];
            }
            node->children = std::vector<Node *>(node->children.begin(),
                                                 node->children.begin() + t);
        }
        auto n = curRoot->keys.size();
        node->keys = std::vector<T>(node->keys.begin(), node->keys.begin() + t);
        curRoot->children.resize(curRoot->children.size() + 1);
        for (int j = n; j >= index + 1; j--) {
            curRoot->children[j + 1] = curRoot->children[j];
        }
        curRoot->children[index + 1] = newChild;
        curRoot->keys.resize(curRoot->keys.size() + 1);
        for (int j = n - 1; j >= int(index); j--) {
            curRoot->keys[j + 1] = curRoot->keys[j];
        }
        curRoot->keys[index] = node->keys[t - 1];
        node->keys = std::vector<T>(node->keys.begin(), node->keys.begin() + t - 1);
    }

    void insertNonFull(Node *node, const T &key) {
        int pos = node->keys.size() - 1;
        if (node->leaf) {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && cmp(key, node->keys[pos])) {
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            node->keys[pos + 1] = key;
        } else {
            while (pos >= 0 && cmp(key, node->keys[pos])) {
                pos--;
            }
            if (isNodeFull(node->children[pos + 1])) {
                splitChild(node, node->children[pos + 1], pos + 1);
                if (!cmp(key, node->keys[pos + 1])) pos++;
            }
            insertNonFull(node->children[pos + 1], key);
        }
    }

    size_t t;
    Node *root;
    Comparator cmp;
};

int main() {
    size_t t = 0;
    std::cin >> t;
    BTree<int, MyComparator<int>> tree(t, MyComparator<int>());
    int val;
    while (std::cin >> val) {
        tree.Insert(val);
    }
    tree.BFSPrint();
    return 0;
}