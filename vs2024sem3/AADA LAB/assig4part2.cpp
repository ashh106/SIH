
// 2. B-Tree Search Efficiency
// Problem Statement: Compare the efficiency of search operations in a B-tree of varying order (t) and size. Implement a B-tree with the following methods:

// -Insert keys into the B-tree.
// -Search for a specific key in the B-tree.
// -Measure and compare the search time complexity for different tree orders and sizes.

// Requirements:
// -Provide a performance analysis and comparison for different B-tree configurations.
// -Ensure that the search operation is optimized for different tree orders.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ORDER 5  // Maximum order to test
#define MAX_SIZE 10000  // Maximum number of keys to test

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
BTreeNode* search(BTreeNode *root, int key);
void splitChild(BTreeNode *parent, int i, int t);
void insertNonFull(BTreeNode *root, int key, int t);
void traverse(BTreeNode *root);
void measureSearchTime(int t, int numKeys);

// Create a new B-Tree node
BTreeNode* createNode(int t, int leaf) {
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->keys = (int*)malloc((2 * t - 1) * sizeof(int));
    node->children = (BTreeNode**)malloc(2 * t * sizeof(BTreeNode*));
    node->numKeys = 0;
    node->leaf = leaf;
    return node;
}

// Insertion into the B-tree
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

// Search for a key in the B-tree
BTreeNode* search(BTreeNode *root, int key) {
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }
    if (i < root->numKeys && root->keys[i] == key) {
        return root;
    }
    if (root->leaf) {
        return NULL;
    }
    return search(root->children[i], key);
}

// Measure and compare search times for different B-tree orders and sizes
void measureSearchTime(int t, int numKeys) {
    BTreeNode *root = createNode(t, 1);  // Create a B-tree with order t and leaf node
    for (int i = 0; i < numKeys; i++) {
        insert(&root, rand() % (numKeys * 2), t);
    }

    // Measure search time
    clock_t start = clock();
    for (int i = 0; i < numKeys; i++) {
        search(root, rand() % (numKeys * 2));
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Order %d, Size %d: Search Time: %f seconds\n", t, numKeys, time_spent);
}

// Main function to run the performance comparison
int main() {
    srand(time(NULL));  // Seed random number generator

    for (int order = 2; order <= MAX_ORDER; order++) {
        for (int size = 1000; size <= MAX_SIZE; size *= 10) {
            measureSearchTime(order, size);
        }
    }

    return 0;
}
