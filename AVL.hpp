#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <stack>

struct Node {
   Node* left;
   Node* right;
   int value;
   int height;

   Node(int _value): value(_value), left(nullptr), right(nullptr), height(0) {}
};

class AVLTree {
private:
   Node* root;

   int subtree_height(Node* ptr) {
      if (ptr == nullptr) {
         return 0;
      }
      return ptr->height;
   }

   int balance(Node* ptr) {
      return subtree_height(ptr->right) - subtree_height(ptr->left);
   }

   void printRecursive(Node* ptr, int indent = 0) {
      if (ptr != nullptr) {
         printRecursive(ptr->right, indent + 5);
         for (int i = 0; i < indent; ++i) {
            std::cout << " ";
         }
         int diff = balance(ptr);
         std::cout << "|-->" << ptr->value << "(" << ptr->height << ")" << std::endl;
         printRecursive(ptr->left, indent + 4);
      }
   }

   void delete_tree(Node* root) {
      if (root != nullptr) {
         delete_tree(root->left);
         delete_tree(root->right);
         delete root;
      }
   }
public:
   AVLTree(): root(nullptr) {}

   ~AVLTree() {
      delete_tree(root);
   }

   void insert(int val) {
      std::stack<Node**> path;
      Node** ptr = &root;

      while((*ptr) != nullptr) {
         path.push(ptr);
         if ((*ptr)->value > val) {
            ptr = &((*ptr)->left);
         } else {
            ptr = &((*ptr)->right);
         }
      }

      *ptr = new Node(val);
      path.push(ptr);

      while(!path.empty()) {
         Node** tmp = path.top();
         path.pop();
         (*tmp)->height = 1 + std::max(subtree_height((*tmp)->left), subtree_height((*tmp)->right));
         int diff = balance((*tmp));
         // std:: cout << (*tmp)->value << " ";

      }
      // std::cout << std::endl;
   }

   bool find(int val) {
      Node* curr = root;
      while(curr != nullptr) {
         if (val == curr->value) {
            return true;
         } else if (val < curr->value) {
            curr = curr->left;
         } else if (val > curr->value) {
            curr = curr->right;
         }
      }

      return false;
   }

   void print() {
      printRecursive(root);
   }
};

#endif