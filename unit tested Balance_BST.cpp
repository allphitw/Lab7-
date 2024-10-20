#include "pch.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Node constructor
Node::Node(const std::string& data) : data(data), left(nullptr), right(nullptr), height(1) {}

// Binary Search Tree constructor
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

// Destructor
BinarySearchTree::~BinarySearchTree() {
    EmptyTree();
}

// Insert a new node into the tree
void BinarySearchTree::Insert(const std::string& data) {
    root = Insert(root, data);
}

// Recursive helper to insert a node and maintain AVL balance
Node* BinarySearchTree::Insert(Node* node, const std::string& data) {
    // Normal BST insertion
    if (node == nullptr) {
        return new Node(data);
    }

    if (data < node->data) {
        node->left = Insert(node->left, data);
    }
    else {
        node->right = Insert(node->right, data);
    }

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor
    int balance = getBalance(node);
    cout << "Inserted " << data << ", Balance at node " << node->data << ": " << balance << endl;

    // If this node becomes unbalanced, there are 4 cases
    // Left Left Case
    if (balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }
    // Right Right Case
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }
    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Return the (unchanged) node pointer
}

// Remove a node with the given data
void BinarySearchTree::Remove(const std::string& data) {
    root = RemoveHelper(root, data);
}

// Recursive helper to remove a node
Node* BinarySearchTree::RemoveHelper(Node* node, const std::string& data) {
    if (node == nullptr) {
        return node;
    }

    if (data < node->data) {
        node->left = RemoveHelper(node->left, data);
    }
    else if (data > node->data) {
        node->right = RemoveHelper(node->right, data);
    }
    else {
        // Node with one child or no child
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp; // Return the new child
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* successor = FindMin(node->right);
        node->data = successor->data; // Copy the inorder successor's data to this node
        node->right = RemoveHelper(node->right, successor->data); // Delete the inorder successor
    }

    // Update height of the current node
    node->height = 1 + max(height(node->left), height(node->right));

    // Balance the node
    int balance = getBalance(node);
    cout << "Removed " << data << ", Balance at node " << node->data << ": " << balance << endl;

    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);
    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);
    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Return the (unchanged) node pointer
}

// Find a node with the given data (search function)
std::string BinarySearchTree::Find(const std::string& data) const {
    Node* current = root;  // Start at the root of the tree

    // Traverse the tree until the node is found or we reach the end
    while (current != nullptr) {
        if (data == current->data) {
            return current->data;  // Found the node, return the data
        }
        else if (data < current->data) {
            current = current->left;  // Move to the left subtree
        }
        else {
            current = current->right;  // Move to the right subtree
        }
    }

    return "";  // Return an empty string if the data is not found
}

// Find the smallest node in a subtree (used internally)
Node* BinarySearchTree::FindMin(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Get the height of the tree
int BinarySearchTree::height(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Get balance factor of node
int BinarySearchTree::getBalance(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Right rotate subtree rooted with y
Node* BinarySearchTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x; // Return new root
}

// Left rotate subtree rooted with x
Node* BinarySearchTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y; // Return new root
}

// Return the size of the tree (number of nodes)
int BinarySearchTree::Size() const {
    return SizeHelper(root);
}

// Recursive helper to count nodes
int BinarySearchTree::SizeHelper(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + SizeHelper(node->left) + SizeHelper(node->right); // Count all nodes
}

// Clear the entire tree
void BinarySearchTree::EmptyTree() {
    root = EmptyTreeHelper(root);
}

// Recursive helper to delete all nodes
Node* BinarySearchTree::EmptyTreeHelper(Node* node) {
    if (node != nullptr) {
        EmptyTreeHelper(node->left);
        EmptyTreeHelper(node->right);
        delete node; // Delete current node
        node = nullptr; // Avoid dangling pointers
    }
    return nullptr;
}

// Print the tree in the specified order
void BinarySearchTree::PrintTree(const std::string& order) const {
    PrintTreeHelper(root, order, 0);
}

// Recursive helper to print the tree
void BinarySearchTree::PrintTreeHelper(Node* node, const std::string& order, int level) const {
    if (node == nullptr) {
        return;
    }

    if (order == "inorder") {
        PrintTreeHelper(node->left, order, level + 1);
        cout << string(level * 2, ' ') << node->data << endl;
        PrintTreeHelper(node->right, order, level + 1);
    }
    else if (order == "preorder") {
        cout << string(level * 2, ' ') << node->data << endl;
        PrintTreeHelper(node->left, order, level + 1);
        PrintTreeHelper(node->right, order, level + 1);
    }
    else if (order == "postorder") {
        PrintTreeHelper(node->left, order, level + 1);
        PrintTreeHelper(node->right, order, level + 1);
        cout << string(level * 2, ' ') << node->data << endl;
    }
}

// Print balance factors of each node in the specified order
void BinarySearchTree::PrintBalanceFactors(const std::string& order) const {
    PrintBalanceFactorsHelper(root, order, 0);
}

// Recursive helper to print balance factors
void BinarySearchTree::PrintBalanceFactorsHelper(Node* node, const std::string& order, int level) const {
    if (node == nullptr) {
        return;
    }

    if (order == "inorder") {
        PrintBalanceFactorsHelper(node->left, order, level + 1);
        cout << string(level * 2, ' ') << node->data << " (Balance: " << getBalance(node) << ")" << endl;
        PrintBalanceFactorsHelper(node->right, order, level + 1);
    }
    else if (order == "preorder") {
        cout << string(level * 2, ' ') << node->data << " (Balance: " << getBalance(node) << ")" << endl;
        PrintBalanceFactorsHelper(node->left, order, level + 1);
        PrintBalanceFactorsHelper(node->right, order, level + 1);
    }
    else if (order == "postorder") {
        PrintBalanceFactorsHelper(node->left, order, level + 1);
        PrintBalanceFactorsHelper(node->right, order, level + 1);
        cout << string(level * 2, ' ') << node->data << " (Balance: " << getBalance(node) << ")" << endl;
    }
}

int main() {
    return 0;
}
