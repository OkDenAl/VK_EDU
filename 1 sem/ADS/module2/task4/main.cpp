// 4 Задача 1 вариант Окутин Денис

//В одной военной части решили построить в одну шеренгу по росту.
//Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
//а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
//Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие,
//а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность –
//все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат,
//а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
//Требуемая скорость выполнения команды - O(log n).
#include <iostream>

class MyComparator {
public:
    bool operator()(const int l, const int r) { return l > r; }
};

struct Node {
    explicit Node(const int data)
            : data(data), left(nullptr), right(nullptr), height(1), count(1) {
    }

    int data;
    int count;
    Node *left;
    Node *right;
    size_t height;
};

template<typename Comparator>
class AVLTree {
public:
    explicit AVLTree(Comparator cmp) : root(nullptr), cmp(cmp) {}

    ~AVLTree() {
        destroyTree(root);
    }

    int FindPos(const int data) {
        Node *tmp = root;
        int fixPos = 0;
        while (true) {
            if (tmp->data == data) {
                return getCount(tmp->left) + fixPos;
            }
            if (cmp(data, tmp->data)) {
                tmp = tmp->left;
            } else {
                fixPos += getCount(tmp->left) + 1;
                tmp = tmp->right;
            }
        }
    }

    void Insert(const int data) {
        root = insertInternal(root, data);
    }

    void Delete(int pos) {
        root = deleteInternal(root, pos);
    }

private:
    size_t getCount(Node *node) {
        return node ? node->count : 0;
    }

    void fixCount(Node *node) {
        node->count = getCount(node->left) + getCount(node->right) + 1;
    }

    size_t getHeight(Node *node) {
        return node ? node->height : 0;
    }

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
        fixCount(node);
        fixHeight(tmp);
        fixCount(tmp);
        return tmp;
    }

    Node *rightRotate(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixCount(node);
        fixHeight(tmp);
        fixCount(tmp);
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
        if (!node)
            return new Node(data);
        if (cmp(node->data, data))
            node->right = insertInternal(node->right, data);
        else
            node->left = insertInternal(node->left, data);
        return doBalance(node);
    }

    Node *doBalance(Node *node) {
        fixHeight(node);
        fixCount(node);
        switch (getBalance(node)) {
            case 2: {
                if (getBalance(node->right) < 0)
                    node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            case -2: {
                if (getBalance(node->left) > 0)
                    node->left = leftRotate(node->left);
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

    Node *deleteInternal(Node *node, int pos) {
        if (!node)
            return nullptr;
        if (pos >= node->count) {
            return node;
        }
        if (getCount(node->left) < pos)
            node->right = deleteInternal(node->right, pos - getCount(node->left) - 1);
        else if (getCount(node->left) > pos)
            node->left = deleteInternal(node->left, pos);
        else {
            Node *left = node->left;
            Node *right = node->right;

            delete node;

            if (!right)
                return left;

            Node *min = findMin(right);
            min->right = removeMinNode(right);
            min->left = left;

            return doBalance(min);
        }

        return doBalance(node);
    }

    Node *root;
    Comparator cmp;
};


int main() {
    int N = 0;
    std::cin >> N;
    AVLTree<MyComparator> root((MyComparator()));
    int val, action = 0;
    for (int i = 0; i < N; i++) {
        std::cin >> action >> val;
        switch (action) {
            case 1:
                root.Insert(val);
                std::cout << root.FindPos(val) << std::endl;
                break;
            case 2:
                root.Delete(val);
                break;
        }
    }
}

