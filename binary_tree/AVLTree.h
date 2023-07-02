#include <iostream>

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    
    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    
    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* temp = newRoot->right;
        
        newRoot->right = node;
        node->left = temp;
        
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
        
        return newRoot;
    }
    
    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* temp = newRoot->left;
        
        newRoot->left = node;
        node->right = temp;
        
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
        
        return newRoot;
    }
    
    Node* insertNode(Node* node, const T& value) {
        if (node == nullptr)
            return new Node(value);
        
        if (value < node->data)
            node->left = insertNode(node->left, value);
        else if (value > node->data)
            node->right = insertNode(node->right, value);
        else
            return node;
        
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        
        int balanceFactor = getBalanceFactor(node);
        
        if (balanceFactor > 1 && value < node->left->data)
            return rotateRight(node);
        
        if (balanceFactor < -1 && value > node->right->data)
            return rotateLeft(node);
        
        if (balanceFactor > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        if (balanceFactor < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    void inOrderTraversal(Node* node, std::ostringstream &actual) {
        if (node != nullptr) {
            inOrderTraversal(node->left, actual);
            actual << node->data << " ";
            inOrderTraversal(node->right, actual);
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(const T& value) {
        root = insertNode(root, value);
    }
    
    void printInOrder(std::ostringstream &actual) {
        inOrderTraversal(root, actual);
        actual << std::endl;
    }
};

