#pragma once
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>

struct Node {
    std::string data;
    Node* left;
    Node* right;
    int height;

    Node(const std::string& data);
};

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();
    void Insert(const std::string& data);
    void Remove(const std::string& data);
    std::string Find(const std::string& data) const; // Use this to find a node by data
    int Size() const;
    void PrintTree(const std::string& order) const; // Function to print the tree
    void PrintBalanceFactors(const std::string& order) const;

private:
    Node* root;
    Node* Insert(Node* node, const std::string& data);
    Node* RemoveHelper(Node* node, const std::string& data);
    Node* FindMin(Node* node);  // Used to find the minimum node in a subtree
    Node* EmptyTreeHelper(Node* node);
    int SizeHelper(Node* node) const;
    void EmptyTree();
    void PrintTreeHelper(Node* node, const std::string& order, int level) const;
    void PrintBalanceFactorsHelper(Node* node, const std::string& order, int level) const;

    int height(Node* node) const;
    int getBalance(Node* node) const;
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
};

#endif // BINARYSEARCHTREE_H
