#include <iostream>
using namespace std;

class TNode {
public:
    int data;
    TNode* left;
    TNode* right;

    // Default Constructor
    TNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TNode* root;

    // Helper function for inserting a node into the BST
    TNode* insertHelper(TNode* node, int value) {
        if (node == nullptr) {
            return new TNode(value);  // Create a new node if the current position is null
        }

        if (value < node->data) {
            node->left = insertHelper(node->left, value);  // Recur on left subtree
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value); // Recur on right subtree
        }

        return node;
    }

    // Helper function for searching a value in the BST
    bool searchHelper(TNode* node, int value) {
        if (node == nullptr) {
            return false;  // Node not found
        }
        if (node->data == value) {
            return true;  // Node found
        }

        return (value < node->data) ? searchHelper(node->left, value) : searchHelper(node->right, value);
    }

    // Helper function for deleting a node in the BST
    TNode* deleteHelper(TNode* node, int value) {
        if (node == nullptr) {
            return node;
        }

        // Search for the node to delete
        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        } else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        } else { // Node to be deleted found
            // Case 1: Node has no children (leaf node)
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2: Node has one child
            if (node->left == nullptr) {
                TNode* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                TNode* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Node has two children
            TNode* temp = findMin(node->right); // Find the minimum node in the right subtree
            node->data = temp->data; // Replace node data with the minimum node's data
            node->right = deleteHelper(node->right, temp->data); // Delete the in-order successor
        }

        return node;
    }

    // Helper function for finding the minimum value node in a given subtree
    TNode* findMin(TNode* node) {
        while (node->left != nullptr) {
            node = node->left;  // Traverse left until we reach the leftmost node
        }
        return node;
    }

    // Helper function for in-order traversal
    void inOrderHelper(TNode* node) {
        if (node == nullptr) {
            return;
        }

        inOrderHelper(node->left); // Visit left subtree
        cout << node->data << " ";  // Print node data
        inOrderHelper(node->right); // Visit right subtree
    }

    // Helper function to get the parent of a node
    TNode* getParentHelper(TNode* node, int value) {
        if (node == nullptr || node->data == value) {
            return nullptr;
        }

        if ((node->left != nullptr && node->left->data == value) || 
            (node->right != nullptr && node->right->data == value)) {
            return node;  // Parent node found
        }

        if (value < node->data) {
            return getParentHelper(node->left, value);
        } else {
            return getParentHelper(node->right, value);
        }
    }

public:
    // Constructor for initializing an empty BST
    BST() : root(nullptr) {}

    // Function to insert a value into the BST
    void insert(int value) {
        root = insertHelper(root, value);  // Start the insertion process from root
    }

    // Function to search for a value in the BST
    bool search(int value) {
        return searchHelper(root, value);  // Start the search process from root
    }

    // Function to delete a node from the BST
    void deleteNode(int value) {
        root = deleteHelper(root, value);  // Start deletion from root
    }

    // Function to check if the BST is empty
    bool isEmpty() {
        return root == nullptr;
    }

    // Function to perform an in-order traversal
    void inOrderTraversal() {
        inOrderHelper(root);  // Start in-order traversal from root
        cout << endl;
    }

    // Function to get the parent of a node
    TNode* getParent(int value) {
        return getParentHelper(root, value);
    }
};

int main() {
    BST tree;

    // Insert nodes into the tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // In-order traversal of the BST
    cout << "In-order Traversal: ";
    tree.inOrderTraversal();

    // Search for a value in the BST
    int searchVal = 40;
    cout << "Searching for " << searchVal << ": "
         << (tree.search(searchVal) ? "Found" : "Not Found") << endl;

    // Find the parent of a node
    int parentVal = 70;
    TNode* parentNode = tree.getParent(parentVal);
    if (parentNode) {
        cout << "Parent of " << parentVal << " is " << parentNode->data << endl;
    } else {
        cout << "No parent found for " << parentVal << endl;
    }

    // Delete a node from the BST
    int deleteVal = 30;
    cout << "Deleting node with value " << deleteVal << endl;
    tree.deleteNode(deleteVal);

    // In-order traversal after deletion
    cout << "In-order Traversal after deletion: ";
    tree.inOrderTraversal();

    return 0;
}

