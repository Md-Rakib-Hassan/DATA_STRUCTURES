/*
If the tree is structured like this:
                    10
                   / \
                 20  30
                /   / \
              40  50  60
                 /     \
                70     80

The input would be: 10 20 30 40 -1 50 60 -1 -1 70 -1 -1 80 -1 -1 -1 -1
This input format uses -1 to represent no child for a node. For example:

                    10
                   /  \
                 20    30
                / \   /  \
              40  -1 50   60
             /\     /\    /\
           -1 -1  70 -1 -1 80
                 / \      / \
               -1  -1   -1  -1
*/

#include <bits/stdc++.h>
using namespace std;
#define nl "\n"

// Node class to represent each node in the tree
class Node {
public:
    int value;
    Node *left;
    Node *right;

    // Constructor to initialize node with a value, left and right set to NULL
    Node(int value) {
        this->value = value;
        left = NULL;
        right = NULL;
    }
};

// Function to take tree input level-wise, with -1 representing a NULL node
Node *inputTree() {
    int value;
    cin >> value;

    Node *root;
    value == -1 ? root = NULL : root = new Node(value); // Root node initialization

    queue<Node *> q; // Queue for level-wise traversal
    if (root) q.push(root); // If root exists, push it to the queue

    // Continue processing nodes in the queue
    while (!q.empty()) {
        Node *currNode = q.front();
        q.pop();

        int lft, rgt;
        Node *left;
        Node *right;

        cin >> lft >> rgt; // Input left and right child values
        lft == -1 ? left = NULL : left = new Node(lft);  // If -1, no left child
        rgt == -1 ? right = NULL : right = new Node(rgt); // If -1, no right child

        currNode->left = left;   // Assign left child
        currNode->right = right; // Assign right child

        if (left) q.push(left); // Push left child to the queue if exists
        if (right) q.push(right); // Push right child to the queue if exists
    }
    return root; // Return the root of the tree
}

// Function for Preorder Traversal (Root -> Left -> Right)
void preorderTraversal(Node *root) {
    if (!root) return;  // If node is NULL return
    
    cout << root->value << " ";   // Visit root
    preorderTraversal(root->left);  // Visit left subtree
    preorderTraversal(root->right); // Visit right subtree
}

// Function for Inorder Traversal (Left -> Root -> Right)
void inorderTraversal(Node *root) {
    if (!root) return; // If node is NULL return

    inorderTraversal(root->left);  // Visit left subtree
    cout << root->value << " ";    // Visit root
    inorderTraversal(root->right); // Visit right subtree
}

// Function for Postorder Traversal (Left -> Right -> Root)
void postorderTraversal(Node *root) {
    if (!root) return; // If nood is NULL return

    postorderTraversal(root->left);  // Visit left subtree
    postorderTraversal(root->right); // Visit right subtree
    cout << root->value << " ";      // Visit root
}

// Function for Level-order Traversal (Breadth-first traversal)
void levelWiseTraversal(Node *root) {
    queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        auto currNode = q.front();
        q.pop();
        cout << currNode->value << " "; // Print current node
        if (currNode->left)
            q.push(currNode->left);   // Push left child to queue
        if (currNode->right)
            q.push(currNode->right);  // Push right child to queue
    }
}

// Function to count total number of nodes in the tree
int countNode(Node *root) {
    if (!root) return 0; // If node is NULL return 0 as it is not a valid node

    int leftSubTree = countNode(root->left);  // Count nodes in left subtree
    int rightSubTree = countNode(root->right); // Count nodes in right subtree
    return leftSubTree + rightSubTree + 1;    // Return total count
}

// Function to count leaf nodes (nodes with no children)
int countLeafNode(Node *root) {
    if (!root) return 0; // If node is NULL return 0 as it is not a valid node
    if (!root->left && !root->right) return 1; // If no children, it's a leaf node
    else {
        int leftSubTree = countLeafNode(root->left);  // Count leaf nodes in left subtree
        int rightSubTree = countLeafNode(root->right); // Count leaf nodes in right subtree
        return leftSubTree + rightSubTree;             // Return total count
    }
}

// Function to calculate the height of the tree (max depth)
int treeHeight(Node *root) {
    if (!root)return 0; // If node is NULL return 0 as it is not a valid node

    int leftSubTree = treeHeight(root->left);   // Height of left subtree
    int rightSubTree = treeHeight(root->right); // Height of right subtree
    return max(leftSubTree, rightSubTree) + 1;  // Return the maximum height + 1 for root
}

int main() {
    Node *root = inputTree(); // Input tree

    if (!root) {
        cout << "No tree to print" << endl; // If tree is empty
        return 0;
    }

    // Perform various traversals and print the results
    cout << "Level Wise Traversal: ";
    levelWiseTraversal(root);
    cout << nl;

    cout << "Preorder traversal: ";
    preorderTraversal(root);
    cout << nl;

    cout << "Inorder traversal: ";
    inorderTraversal(root);
    cout << nl;

    cout << "Postorder traversal: ";
    postorderTraversal(root);
    cout << nl;

    // Print total nodes, leaf nodes, and tree height
    cout << "Total Nodes: ";
    cout << countNode(root) << nl;

    cout << "Total Leaf Nodes: ";
    cout << countLeafNode(root) << nl;

    cout << "Tree Height: ";
    cout << treeHeight(root) << nl;

    return 0;
}
