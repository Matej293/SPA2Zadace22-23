#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int key;
    Node *left, *right, *parent;
};

class BST {
    Node *root;

    Node* insert(int key, Node *node) {
        if (node == nullptr)
            return new Node{key, nullptr, nullptr, nullptr};

        if (key < node->key) {
            Node *lchild = insert(key, node->left);
            node->left = lchild;
            lchild->parent = node;
        }
        else if (key > node->key) {
            Node *rchild = insert(key, node->right);
            node->right = rchild;
            rchild->parent = node;
        }

        return node;
    }

    void inorder(Node *node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
        else return;
    }

    Node* search(int key, Node *node) {
        if (node == nullptr || key == node->key)
            return node;

        if (key > node->key)
            search(key, node->right);
        else
            search(key, node->left);
    }

    static Node* find_min(Node* node) {
        while(node->left != nullptr)
            node = node->left;
        return node;
    }

    static Node* find_max(Node* node) {
        while(node->right != nullptr)
            node = node->right;
        return node;
    }


    static Node* successor(Node *node) {
        if(node->right != nullptr)
            return find_min(node->right);

        Node* y = node->parent;
        while( y != nullptr && node == y->right){
            node = y;
            y = y->parent;
        }
        return y;
    }

    static Node* predecessor(Node* node) {
        if(node->left != nullptr)
            return find_max(node->left);

        Node* y = node->parent;
        while( y != nullptr && node == y->left){
            node = y;
            y = y->parent;
        }
        return y;
    }


    Node* BSTdelete(int key, Node *node) {
        if (node == nullptr)
            return node;

        if (key < node->key) {
            node->left = BSTdelete(key, node->left);
            if (node->left != nullptr)
                node->left->parent = node;
        }
        else if (key > node->key) {
            node->right = BSTdelete(key, node->right);
            if (node->right != nullptr)
                node->right->parent = node;
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = find_min(node->right);

            node->key = temp->key;

            node->right = BSTdelete(temp->key, node->right);
        }

        return node;
    }

public:
    BST() : root(nullptr) {}

    void print() {
        inorder(root);
        cout << "\n";
    }

    void insert(int key) {
        root = insert(key, root);
    }

    bool search(int key) {
        return search(key, root) != nullptr;
    }

    int find_min() {
        return find_min(root)->key;
    }

    int find_max() {
        return find_max(root)->key;
    }

    int successor(int key) {
        Node* temp = search(key, root);
        return successor(temp)->key;
    }

    int predecessor(int key) {
        Node* temp = search(key, root);
        return predecessor(temp)->key;
    }

    void BSTdelete(int key) {
        root = BSTdelete(key, root);
    }
};

int main() {
    BST bst;

    vector<int> keys{5, 10, 4, 8, 9, 1, 11, 15, 3};
    for (int key : keys)
        bst.insert(key);
    
    bst.print();

    cout << bst.find_min() << "\n";
    cout << bst.find_max() << "\n";
    cout << bst.successor(8) << "\n";
    cout << bst.predecessor(10) << "\n";

    bst.BSTdelete(10);
    bst.print();

    return 0;
}