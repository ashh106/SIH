// lab 1 - bfs/dfs
// Task 1.
// AVL TREE
//Implement an AVL Tree with basic operations: 
//insertion, deletion, and in-order traversal. 
//Ensure that the tree maintains its 
//balance property after each insertion or deletion.
// bst with ballance factor (0, 1, -1)

            // x
            //  \
            //   y 
            //    \ 
            //     z 

#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int key; //root node
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
};
int height(struct TreeNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
struct TreeNode* newNode(int key) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return(node);
}
struct TreeNode *rightRotate(struct TreeNode *y) {
    struct TreeNode *x = y->left;
    struct TreeNode *T2 = x->right;
    //       y            t2
        //    \            \
        //     x            x
        //    /            /
        //   t2           y
    // Perform rotation
    x->right = y;
    y->left = T2;
    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    // Return new root
    return x;
}
struct TreeNode *leftRotate(struct TreeNode *x) {
    struct TreeNode *y = x->right;
    struct TreeNode *T2 = y->left;
    // Perform rotation
    y->left = x;
    x->right = T2;
    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}
// Get Balance factor of node N
int getBalance(struct TreeNode *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
// insert a key in the subtree rooted with node and returns the new root of the subtree
struct TreeNode* insert(struct TreeNode* node, int key) {
    // 1. Perform the normal BST rotation
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else  // Equal keys are not allowed in BST
        return node;

    // 2. Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // return the (unchanged) node pointer
    return node;
}

// Function to find the node with the smallest key value found in a tree
struct TreeNode *minValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;

    // loop down to find the leftmost leaf
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given key from subtree with given root. It returns root of the modified subtree.
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node to be deleted
    else {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct TreeNode *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        }
        else {
            // node with two children: Get the inorder successor (smallest in the right subtree)
            struct TreeNode* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to do inorder traversal of the tree
void inOrder(struct TreeNode *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

int main() {
    struct TreeNode *root = NULL;

    /* Constructing tree given in the above figure */
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    /* The constructed AVL Tree would be
                9
               /  \
              1    10
            /  \     \
           0    5     11
          /    /  \
         -1   2    6
    */

    printf("Inorder traversal of the constructed AVL tree is \n");
    inOrder(root);

    root = deleteNode(root, 10);

    /* The AVL Tree after deletion of 10
                1
               /  \
              0    9
            /     /  \
           -1    5     11
               /  \
              2    6
    */

    printf("\nInorder traversal after deletion of 10 \n");
    inOrder(root);

    return 0;
}

