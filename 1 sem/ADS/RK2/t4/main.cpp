// Рк 2 Окутин Денис
// Реализуйте AVL-дерево. Решения с использованием других структур засчитываться
// не будут. Входной файл содержит описание операций с деревом. Операций не
// больше 105.

#include <iostream>
#include <vector>

struct Node {
    explicit Node(const int data)
            : data(data), left(nullptr), right(nullptr), height(1) {}

    int data;
    Node *left;
    Node *right;
    size_t height;
};

class AVLTree {
public:
    explicit AVLTree() : root(nullptr) {}

    ~AVLTree() { destroyTree(root); }

    bool Has(int data) {
        Node *tmp = root;
        while (tmp) {
            if (tmp->data == data)
                return true;
            else if (tmp->data < data)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        return false;
    }

    std::pair<int, bool> Next(int data) {
        std::vector<int> greaterThenData;
        Node *tmp = root;
        while (tmp) {
            if (tmp->data <= data)
                tmp = tmp->right;
            else {
                greaterThenData.push_back(tmp->data);
                tmp = tmp->left;
            }
        }

        if (greaterThenData.empty()) {
            return std::make_pair(0, false);
        }
        int min = greaterThenData[0];
        for (size_t i = 1; i < greaterThenData.size(); i++) {
            if (greaterThenData[i] < min) {
                min = greaterThenData[i];
            }
        }
        return std::make_pair(min, true);
    }

    std::pair<int, bool> Prev(int data) {
        std::vector<int> lessThenData;
        Node *tmp = root;
        while (tmp) {
            if (tmp->data < data) {
                lessThenData.push_back(tmp->data);
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }

        if (lessThenData.empty()) {
            return std::make_pair(0, false);
        }
        int max = lessThenData[0];
        for (size_t i = 1; i < lessThenData.size(); i++) {
            if (lessThenData[i] > max) {
                max = lessThenData[i];
            }
        }
        return std::make_pair(max, true);
    }

    void Insert(int data) {
        if (!Has(data)) {
            root = insertInternal(root, data);
        }
    }

    void Delete(int data) {
        if (Has(data)) {
            root = deleteInternal(root, data);
        }
    }

private:
    size_t getHeight(Node *node) { return node ? node->height : 0; }

    void fixHeight(Node *node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalance(Node *node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    Node *leftRotate(Node *node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

    Node *rightRotate(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

    void destroyTree(Node *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node *insertInternal(Node *node, int data) {
        if (!node) return new Node(data);
        if (node->data < data)
            node->right = insertInternal(node->right, data);
        else
            node->left = insertInternal(node->left, data);

        return doBalance(node);
    }

    Node *doBalance(Node *node) {
        fixHeight(node);
        switch (getBalance(node)) {
            case 2: {
                if (getBalance(node->right) < 0) node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            case -2: {
                if (getBalance(node->left) > 0) node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            default:
                return node;
        }
    }

    Node *findMin(Node *node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node *removeMinNode(Node *node) {
        if (!node->left) {
            return node->right;
        }
        node->left = removeMinNode(node->left);
        return doBalance(node);
    }

    Node *deleteInternal(Node *node, int data) {
        if (!node) return nullptr;
        if (node->data < data)
            node->right = deleteInternal(node->right, data);
        else if (node->data > data)
            node->left = deleteInternal(node->left, data);
        else {
            Node *left = node->left;
            Node *right = node->right;

            delete node;

            if (!right) return left;
            Node *min = findMin(right);
            min->right = removeMinNode(right);
            min->left = left;

            return doBalance(min);
        }

        return doBalance(node);
    }

    Node *root;
};

int main() {
    AVLTree root;
    std::string action;
    int val;
    while (std::cin >> action >> val) {
        if (action == "insert") {
            root.Insert(val);
        } else if (action == "delete") {
            root.Delete(val);
        } else if (action == "exists") {
            if (root.Has(val)) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        } else if (action == "next") {
            std::pair<int, bool> resp = root.Next(val);
            if (resp.second) {
                std::cout << resp.first << std::endl;
            } else {
                std::cout << "none" << std::endl;
            }
        } else if (action == "prev") {
            std::pair<int, bool> resp = root.Prev(val);
            if (resp.second) {
                std::cout << resp.first << std::endl;
            } else {
                std::cout << "none" << std::endl;
            }
        }
    }
    return 0;
}
