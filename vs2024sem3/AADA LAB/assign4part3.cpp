
// 3. B-Tree Range Queries
// Problem Statement: Implement range queries in a B-tree to find all keys within a given range [k1, k2]. Provide methods to:

// -Insert keys into the B-tree.
// -Perform a range query to find all keys between k1 and k2.
// -Display the results of the range query.

// Requirements:
// -Ensure that the range query is efficient and works correctly with various tree sizes and ranges.


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
void rangeQuery(BTreeNode *root, int k1, int k2);
void rangeQueryUtil(BTreeNode *root, int k1, int k2);
void printInOrder(BTreeNode *root);

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

// Perform a range query in the B-tree
void rangeQuery(BTreeNode *root, int k1, int k2) {
    if (root == NULL) return;
    rangeQueryUtil(root, k1, k2);
}

// Helper function for range query
void rangeQueryUtil(BTreeNode *root, int k1, int k2) {
    int i = 0;
    while (i < root->numKeys && k2 < root->keys[i]) {
        i++;
    }
    if (i < root->numKeys && k1 <= root->keys[i] && root->keys[i] <= k2) {
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) {
        for (int j = i; j <= root->numKeys && (j < root->numKeys && root->keys[j] <= k2); j++) {
            rangeQueryUtil(root->children[j], k1, k2);
        }
        if (i < root->numKeys) {
            rangeQueryUtil(root->children[i + 1], k1, k2);
        }
    }
}

// Print the B-tree in-order (for debugging)
void printInOrder(BTreeNode *root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->numKeys; i++) {
            if (!root->leaf) {
                printInOrder(root->children[i]);
            }
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf) {
            printInOrder(root->children[i]);
        }
    }
}

// Main function to test B-Tree with range queries
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

    // Print the B-tree (for verification)
    printf("B-Tree In-Order Traversal:\n");
    printInOrder(root);
    printf("\n");

    // Perform range query
    int k1 = 5, k2 = 25;
    printf("Keys in range [%d, %d]:\n", k1, k2);
    rangeQuery(root, k1, k2);
    printf("\n");

    return 0;
}
