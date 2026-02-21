#pragma once
#pragma once
#include <iostream>
#include <string>
using namespace std;

// ==================== N-ARY TREE NODE ====================
// General tree node that can have any number of children
// Used for: Islamabad sector hierarchy, organizational structures
class TreeNode {
public:
    int id;                    // Node identifier
    string name;               // Node name/label
    void* data;                // Generic pointer to store any object
    TreeNode** children;       // Array of child pointers
    int childCount;            // Current number of children
    int capacity;              // Maximum children capacity

    // Constructor
    TreeNode(int val, int cap = 10, string nodeName = "") {
        id = val;
        name = nodeName;
        data = nullptr;
        capacity = cap;
        childCount = 0;
        children = new TreeNode * [cap];
        for (int i = 0; i < cap; i++) {
            children[i] = nullptr;
        }
    }

    // Destructor
    ~TreeNode() {
        delete[] children;
    }

    // Add a child node - O(1)
    bool addChild(TreeNode* node) {
        if (childCount < capacity) {
            children[childCount++] = node;
            return true;
        }
        return false;
    }

    // Remove a child by ID - O(n) where n is number of children
    bool removeChild(int childId) {
        for (int i = 0; i < childCount; i++) {
            if (children[i]->id == childId) {
                // Shift remaining children left
                for (int j = i; j < childCount - 1; j++) {
                    children[j] = children[j + 1];
                }
                childCount--;
                children[childCount] = nullptr;
                return true;
            }
        }
        return false;
    }

    // Find child by ID - O(n)
    TreeNode* findChild(int childId) {
        for (int i = 0; i < childCount; i++) {
            if (children[i]->id == childId) {
                return children[i];
            }
        }
        return nullptr;
    }

    // Get child at specific index - O(1)
    TreeNode* getChild(int index) {
        if (index >= 0 && index < childCount) {
            return children[index];
        }
        return nullptr;
    }

    // Check if node is leaf - O(1)
    bool isLeaf() {
        return childCount == 0;
    }

    // Set data pointer - O(1)
    void setData(void* dataPtr) {
        data = dataPtr;
    }

    // Get data pointer - O(1)
    void* getData() {
        return data;
    }

    // Print node information - O(n) where n is number of children
    void print() {
        cout << "Node " << id;
        if (name != "") {
            cout << " (" << name << ")";
        }
        cout << " -> Children: ";
        for (int i = 0; i < childCount; i++) {
            cout << children[i]->id;
            if (i < childCount - 1) cout << ", ";
        }
        if (childCount == 0) cout << "None";
        cout << endl;
    }
};


// ==================== N-ARY TREE CLASS ====================
// General tree structure for hierarchical data
// Used for: Islamabad administrative hierarchy (Sector->Street->House)
class NaryTree {
private:
    TreeNode* root;
    int nodeCount;

    // Helper: Recursive preorder traversal - O(n)
    void preorderHelper(TreeNode* node) {
        if (node == nullptr) return;
        node->print();
        for (int i = 0; i < node->childCount; i++) {
            preorderHelper(node->children[i]);
        }
    }

    // Helper: Recursive postorder traversal - O(n)
    void postorderHelper(TreeNode* node) {
        if (node == nullptr) return;
        for (int i = 0; i < node->childCount; i++) {
            postorderHelper(node->children[i]);
        }
        node->print();
    }

    // Helper: Find node by ID recursively - O(n)
    TreeNode* findNodeHelper(TreeNode* node, int id) {
        if (node == nullptr) return nullptr;
        if (node->id == id) return node;

        for (int i = 0; i < node->childCount; i++) {
            TreeNode* found = findNodeHelper(node->children[i], id);
            if (found != nullptr) return found;
        }
        return nullptr;
    }

    // Helper: Calculate tree height - O(n)
    int heightHelper(TreeNode* node) {
        if (node == nullptr) return 0;
        if (node->isLeaf()) return 1;

        int maxHeight = 0;
        for (int i = 0; i < node->childCount; i++) {
            int childHeight = heightHelper(node->children[i]);
            if (childHeight > maxHeight) {
                maxHeight = childHeight;
            }
        }
        return maxHeight + 1;
    }

    // Helper: Count total nodes - O(n)
    int countNodesHelper(TreeNode* node) {
        if (node == nullptr) return 0;
        int count = 1;
        for (int i = 0; i < node->childCount; i++) {
            count += countNodesHelper(node->children[i]);
        }
        return count;
    }

    // Helper: Delete tree recursively - O(n)
    void deleteTreeHelper(TreeNode* node) {
        if (node == nullptr) return;
        for (int i = 0; i < node->childCount; i++) {
            deleteTreeHelper(node->children[i]);
        }
        delete node;
    }

    // Helper: Print tree structure with indentation - O(n)
    void printTreeHelper(TreeNode* node, int level) {
        if (node == nullptr) return;

        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        cout << "|- " << node->id;
        if (node->name != "") {
            cout << " (" << node->name << ")";
        }
        cout << endl;

        for (int i = 0; i < node->childCount; i++) {
            printTreeHelper(node->children[i], level + 1);
        }
    }

public:
    // Constructor
    NaryTree() {
        root = nullptr;
        nodeCount = 0;
    }

    // Destructor
    ~NaryTree() {
        clear();
    }

    // Set root node - O(1)
    void setRoot(TreeNode* node) {
        root = node;
        nodeCount = 1;
    }

    // Get root node - O(1)
    TreeNode* getRoot() {
        return root;
    }

    // Find node by ID - O(n)
    TreeNode* findNode(int id) {
        return findNodeHelper(root, id);
    }

    // Add child to a specific parent node - O(n) for finding parent
    bool addNode(int parentId, TreeNode* childNode) {
        if (root == nullptr) {
            root = childNode;
            nodeCount = 1;
            return true;
        }

        TreeNode* parent = findNode(parentId);
        if (parent != nullptr) {
            if (parent->addChild(childNode)) {
                nodeCount++;
                return true;
            }
        }
        return false;
    }

    // Remove a node and its subtree - O(n)
    bool removeNode(int id) {
        if (root == nullptr) return false;
        if (root->id == id) {
            deleteTreeHelper(root);
            root = nullptr;
            nodeCount = 0;
            return true;
        }

        TreeNode* parent = findParent(root, id);
        if (parent != nullptr) {
            TreeNode* nodeToRemove = parent->findChild(id);
            if (nodeToRemove != nullptr) {
                int subtreeCount = countNodesHelper(nodeToRemove);
                deleteTreeHelper(nodeToRemove);
                parent->removeChild(id);
                nodeCount -= subtreeCount;
                return true;
            }
        }
        return false;
    }

    // Find parent of a node - O(n)
    TreeNode* findParent(TreeNode* current, int childId) {
        if (current == nullptr) return nullptr;

        for (int i = 0; i < current->childCount; i++) {
            if (current->children[i]->id == childId) {
                return current;
            }
            TreeNode* found = findParent(current->children[i], childId);
            if (found != nullptr) return found;
        }
        return nullptr;
    }

    // Get tree height - O(n)
    int getHeight() {
        return heightHelper(root);
    }

    // Get total node count - O(n)
    int getNodeCount() {
        return countNodesHelper(root);
    }

    // Check if tree is empty - O(1)
    bool isEmpty() {
        return root == nullptr;
    }

    // Preorder traversal - O(n)
    void preorderTraversal() {
        cout << "Preorder Traversal:" << endl;
        preorderHelper(root);
    }

    // Postorder traversal - O(n)
    void postorderTraversal() {
        cout << "Postorder Traversal:" << endl;
        postorderHelper(root);
    }

    // Print tree structure - O(n)
    void printTree() {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return;
        }
        cout << "Tree Structure:" << endl;
        printTreeHelper(root, 0);
    }

    // Clear entire tree - O(n)
    void clear() {
        deleteTreeHelper(root);
        root = nullptr;
        nodeCount = 0;
    }
};



