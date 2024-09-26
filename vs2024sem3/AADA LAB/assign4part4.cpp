// 4. B-Tree Traversals and Visualizations
// Problem Statement: Implement and visualize different traversals of a B-tree (in-order, pre-order, post-order). Provide methods to:

// -Insert keys into the B-tree.
// -Perform and display in-order, pre-order, and post-order traversals of the B-tree.
// -Generate a visual representation of the B-tree structure.

// Requirements:
// -Ensure that traversals are implemented correctly and efficiently.
// -Use appropriate libraries or techniques to visualize the B-tree structure.

#include <stdio.h>
#include <stdlib.h>

#define T 3  // Minimum degree (order/2)

// B-Tree Node structure
typedef struct BTreeNode {
    int *keys;              // Array of keys
    struct BTreeNode **children; // Array of child pointers
    int numKeys;            // Number of keys currently in the node
    int leaf;               // 1 if leaf node, 0 otherwise
} BTreeNode;

// Function prototypes
BTreeNode* createNode(int t, int leaf);
void insert(BTreeNode **root, int key, int t);
void splitChild(BTreeNode *parent, int i, int t);
void insertNonFull(BTreeNode *root, int key, int t);
void traverseInOrder(BTreeNode *root);
void traversePreOrder(BTreeNode *root);
void traversePostOrder(BTreeNode *root);
void visualizeBTree(BTreeNode *root, int level);

// Create a new B-Tree node
BTreeNode* createNode(int t, int leaf) {
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->keys = (int*)malloc((2 * t - 1) * sizeof(int));
    node->children = (BTreeNode**)malloc(2 * t * sizeof(BTreeNode*));
    node->numKeys = 0;
    node->leaf = leaf;
    return node;
}

// Insert a key into the B-tree
void insert(BTreeNode **root, int key, int t) {
    BTreeNode *r = *root;
    if (r->numKeys == 2 * t - 1) {
        BTreeNode *s = createNode(t, 0);
        *root = s;
        s->children[0] = r;
        splitChild(s, 0, t);
        insertNonFull(s, key, t);
    } else {
        insertNonFull(r, key, t);
    }
}

// Insert a key into a non-full node
void insertNonFull(BTreeNode *root, int key, int t) {
    int i = root->numKeys - 1;
    if (root->leaf) {
        while (i >= 0 && key < root->keys[i]) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = key;
        root->numKeys += 1;
    } else {
        while (i >= 0 && key < root->keys[i]) {
            i--;
        }
        i++;
        if (root->children[i]->numKeys == 2 * t - 1) {
            splitChild(root, i, t);
            if (key > root->keys[i]) {
                i++;
            }
        }
        insertNonFull(root->children[i], key, t);
    }
}

// Split the child of a B-Tree node
void splitChild(BTreeNode *parent, int i, int t) {
    BTreeNode *child = parent->children[i];
    BTreeNode *newChild = createNode(t, child->leaf);
    parent->children[i + 1] = newChild;
    parent->keys[i] = child->keys[t - 1];
    newChild->numKeys = t - 1;
    child->numKeys = t - 1;

    for (int j = 0; j < t - 1; j++) {
        newChild->keys[j] = child->keys[j + t];
    }
    if (!child->leaf) {
        for (int j = 0; j < t; j++) {
            newChild->children[j] = child->children[j + t];
        }
    }
}

// In-order traversal of the B-tree
void traverseInOrder(BTreeNode *root) {
    if (root == NULL) return;

    int i;
    for (i = 0; i < root->numKeys; i++) {
        if (!root->leaf) {
            traverseInOrder(root->children[i]);
        }
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) {
        traverseInOrder(root->children[i]);
    }
}

// Pre-order traversal of the B-tree
void traversePreOrder(BTreeNode *root) {
    if (root == NULL) return;

    int i;
    printf("%d ", root->keys[0]);  // Print the first key of the node
    for (i = 0; i < root->numKeys; i++) {
        if (!root->leaf) {
            traversePreOrder(root->children[i]);
        }
    }
    if (!root->leaf) {
        traversePreOrder(root->children[i]);
    }
}

// Post-order traversal of the B-tree
void traversePostOrder(BTreeNode *root) {
    if (root == NULL) return;

    int i;
    for (i = 0; i < root->numKeys; i++) {
        if (!root->leaf) {
            traversePostOrder(root->children[i]);
        }
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) {
        traversePostOrder(root->children[i]);
    }
}

// Visualize the B-tree structure
void visualizeBTree(BTreeNode *root, int level) {
    if (root == NULL) return;

    printf("Level %d: ", level);
    for (int i = 0; i < root->numKeys; i++) {
        printf("%d ", root->keys[i]);
    }
    printf("\n");

    if (!root->leaf) {
        for (int i = 0; i <= root->numKeys; i++) {
            visualizeBTree(root->children[i], level + 1);
        }
    }
}

// Main function to test B-Tree traversals and visualization
int main() {
    BTreeNode *root = createNode(T, 1);  // Create a B-tree with order T and leaf node

    // Insert keys into the B-tree
    insert(&root, 10, T);
    insert(&root, 20, T);
    insert(&root, 5, T);
    insert(&root, 6, T);
    insert(&root, 15, T);
    insert(&root, 30, T);
    insert(&root, 25, T);

    // Perform and display traversals
    printf("In-Order Traversal:\n");
    traverseInOrder(root);
    printf("\n");

    printf("Pre-Order Traversal:\n");
    traversePreOrder(root);
    printf("\n");

    printf("Post-Order Traversal:\n");
    traversePostOrder(root);
    printf("\n");

    // Visualize the B-tree structure
    printf("B-Tree Visualization:\n");
    visualizeBTree(root, 0);

    return 0;
}

