// 1. B-Tree Insertion and Deletion
// Problem Statement: Implement a B-tree with a given order (t) and support for insertion and deletion operations. Provide methods to:

// -Insert a key into the B-tree.
// -Delete a key from the B-tree.
// -Display the B-tree in-order traversal.

// Requirements:
// -The B-tree must maintain its properties after each insertion or deletion.
// -Implement appropriate splitting and merging of nodes.


#include <stdio.h>
#include <stdlib.h>

#define T 3  // Minimum degree (order/2)

typedef struct BTreeNode {
    int *keys;             // Array of keys
    struct BTreeNode **children; // Array of child pointers
    int numKeys;           // Number of keys currently in the node
    int leaf;              // 1 if leaf node, 0 otherwise
} BTreeNode;

// Create a new B-Tree node
BTreeNode* createNode(int t, int leaf) {
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->keys = (int*)malloc((2*t - 1) * sizeof(int));
    node->children = (BTreeNode**)malloc(2*t * sizeof(BTreeNode*));
    node->numKeys = 0;
    node->leaf = leaf;
    return node;
}

// A utility function to traverse the B-tree in-order
void traverse(BTreeNode *root) {
    int i;
    if (root != NULL) {
        for (i = 0; i < root->numKeys; i++) {
            if (!root->leaf) {
                traverse(root->children[i]);
            }
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf) {
            traverse(root->children[i]);
        }
    }
}

// insert node

void insertNonFull(BTreeNode *root, int key, int t) {
    int i = root->numKeys - 1;

    if (root->leaf) {
        // Insert the new key into the leaf node
        while (i >= 0 && key < root->keys[i]) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = key;
        root->numKeys += 1;
    } else {
        // Find the child which is going to have the new key
        while (i >= 0 && key < root->keys[i]) {
            i--;
        }
        i++;
        if (root->children[i]->numKeys == 2*t - 1) {
            splitChild(root, i, t);
            if (key > root->keys[i]) {
                i++;
            }
        }
        insertNonFull(root->children[i], key, t);
    }
}

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

// Insert a key into the B-tree
void insert(BTreeNode **root, int key, int t) {
    BTreeNode *r = *root;
    if (r->numKeys == 2*t - 1) {
        BTreeNode *s = createNode(t, 0);
        *root = s;
        s->children[0] = r;
        splitChild(s, 0, t);
        insertNonFull(s, key, t);
    } else {
        insertNonFull(r, key, t);
    }
}
//delete

void deleteKey(BTreeNode *root, int key, int t);

void removeFromLeaf(BTreeNode *node, int idx) {
    for (int i = idx + 1; i < node->numKeys; ++i) {
        node->keys[i - 1] = node->keys[i];
    }
    node->numKeys--;
}

void removeFromNonLeaf(BTreeNode *node, int idx, int t) {
    int k = node->keys[idx];

    if (node->children[idx]->numKeys >= t) {
        int pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        deleteKey(node->children[idx], pred, t);
    } else if (node->children[idx + 1]->numKeys >= t) {
        int succ = getSuccessor(node, idx);
        node->keys[idx] = succ;
        deleteKey(node->children[idx + 1], succ, t);
    } else {
        merge(node, idx, t);
        deleteKey(node->children[idx], k, t);
    }
}

int getPredecessor(BTreeNode *node, int idx) {
    BTreeNode *cur = node->children[idx];
    while (!cur->leaf) {
        cur = cur->children[cur->numKeys];
    }
    return cur->keys[cur->numKeys - 1];
}

int getSuccessor(BTreeNode *node, int idx) {
    BTreeNode *cur = node->children[idx + 1];
    while (!cur->leaf) {
        cur = cur->children[0];
    }
    return cur->keys[0];
}

void merge(BTreeNode *node, int idx, int t) {
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx + 1];
    int t_1 = t - 1;

    child->keys[t_1] = node->keys[idx];

    for (int i = 0; i < sibling->numKeys; ++i) {
        child->keys[i + t] = sibling->keys[i];
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->numKeys; ++i) {
            child->children[i + t] = sibling->children[i];
        }
    }

    for (int i = idx + 1; i < node->numKeys; ++i) {
        node->keys[i - 1] = node->keys[i];
    }

    for (int i = idx + 2; i <= node->numKeys; ++i) {
        node->children[i - 1] = node->children[i];
    }

    child->numKeys += sibling->numKeys + 1;
    node->numKeys--;
    free(sibling->keys);
    free(sibling->children);
    free(sibling);
}

void deleteKey(BTreeNode *root, int key, int t) {
    int idx = findKey(root, key);
    if (idx < root->numKeys && root->keys[idx] == key) {
        if (root->leaf) {
            removeFromLeaf(root, idx);
        } else {
            removeFromNonLeaf(root, idx, t);
        }
    } else {
        if (root->leaf) {
            printf("The key %d is not present in the tree.\n", key);
            return;
        }
        int flag = (idx == root->numKeys) ? 1 : 0;

        if (root->children[idx]->numKeys < t) {
            fill(root, idx, t);
        }
        if (flag && idx > root->numKeys) {
            deleteKey(root->children[idx - 1], key, t);
        } else {
            deleteKey(root->children[idx], key, t);
        }
    }
}

int findKey(BTreeNode *node, int key) {
    int idx = 0;
    while (idx < node->numKeys && node->keys[idx] < key) {
        ++idx;
    }
    return idx;
}


int main() {
    BTreeNode *root = createNode(T, 1);

    insert(&root, 10, T);
    insert(&root, 20, T);
    insert(&root, 5, T);
    insert(&root, 6, T);
    insert(&root, 15, T);
    insert(&root, 30, T);
    insert(&root, 25, T);
    insert(&root, 40, T);
    insert(&root, 50, T);

    printf("In-order traversal of the B-tree:\n");
    traverse(root);
    printf("\n");

    deleteKey(root, 6, T);
    printf("In-order traversal after deletion of 6:\n");
    traverse(root);
    printf("\n");

    return 0;
}


