#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;
    int t; // Minimum degree

    BTreeNode(int _t, bool _leaf);

    void traverse();
    void traverseInOrder();
    void traversePreOrder();
    void traversePostOrder();

    BTreeNode* search(int k);
    void insertNonFull(int k);
    void splitChild(int i);ṇ

    void deleteKey(int k);
    void removeKey(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

class BTree {
public:
    BTreeNode* root;
    int t; // Minimum degree

    BTree(int _t) : t(_t) {
        root = new BTreeNode(t, true);
    }

    void traverse() {
        if (root != nullptr) root->traverse();
    }

    void insert(int k);
    void remove(int k);
    BTreeNode* search(int k);
    vector<int> rangeQuery(int k1, int k2);

    void traverseInOrder() {
        if (root != nullptr) root->traverseInOrder();
        cout << endl;
    }

    void traversePreOrder() {
        if (root != nullptr) root->traversePreOrder();
        cout << endl;
    }

    void traversePostOrder() {
        if (root != nullptr) root->traversePostOrder();
        cout << endl;
    }
};

BTreeNode::BTreeNode(int _t, bool _leaf) : t(_t), leaf(_leaf) {}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!leaf) children[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf) children[i]->traverse();
}

void BTreeNode::traverseInOrder() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!leaf) children[i]->traverseInOrder();
        cout << " " << keys[i];
    }
    if (!leaf) children[i]->traverseInOrder();
}

void BTreeNode::traversePreOrder() {
    cout << " ";
    for (int key : keys) cout << key << " ";
    if (!leaf) {
        for (BTreeNode* child : children) child->traversePreOrder();
    }
}

void BTreeNode::traversePostOrder() {
    if (!leaf) {
        for (BTreeNode* child : children) child->traversePostOrder();
    }
    for (int key : keys) cout << key << " ";
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < keys.size() && k > keys[i]) i++;
    if (i < keys.size() && keys[i] == k) return this;
    if (leaf) return nullptr;
    return children[i]->search(k);
}

void BTreeNode::insertNonFull(int k) {
    int i = keys.size() - 1;
    if (leaf) {
        keys.push_back(0); // Add a dummy element
        while (i >= 0 && k < keys[i]) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && k < keys[i]) i--;
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1);
            if (k > keys[i + 1]) i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i) {
    BTreeNode* y = children[i];
    BTreeNode* z = new BTreeNode(t, y->leaf);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
    children.insert(children.begin() + i + 1, z);

    z->keys.assign(y->keys.begin() + t, y->keys.end());
    y->keys.resize(t - 1);

    if (!y->leaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }
}

void BTreeNode::removeKey(int k) {
    // Implementation of delete function
    int idx = 0;
    while (idx < keys.size() && keys[idx] < k) idx++;

    if (idx < keys.size() && keys[idx] == k) {
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        if (leaf) {
            return;
        }
        bool flag = (idx == keys.size());
        if (children[idx]->keys.size() < t) fill(idx);

        if (flag && idx > keys.size()) {
            children[idx - 1]->removeKey(k);
        } else {
            children[idx]->removeKey(k);
        }
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    if (children[idx]->keys.size() >= t) {
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->removeKey(pred);
    } else if (children[idx + 1]->keys.size() >= t) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx + 1]->removeKey(succ);
    } else {
        merge(idx);
        children[idx]->removeKey(k);
    }
}

int BTreeNode::getPred(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->leaf) cur = cur->children.back();
    return cur->keys.back();
}

int BTreeNode::getSucc(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf) cur = cur->children.front();
    return cur->keys.front();
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->keys.size() >= t) {
        borrowFromPrev(idx);
    } else if (idx != keys.size() && children[idx + 1]->keys.size() >= t) {
        borrowFromNext(idx);
    } else {
        if (idx != keys.size()) merge(idx);
        else merge(idx - 1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];

    child->keys.insert(child->keys.begin(), keys[idx - 1]);
    keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();

    if (!child->leaf) {
        child->children.insert(child->children.begin(), sibling->children.back());
        sibling->children.pop_back();
    }
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    keys[idx] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());

    if (!child->leaf) {
        child->children.push_back(sibling->children.front());
        sibling->children.erase(sibling->children.begin());
    }
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());

    if (!child->leaf) {
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);
    delete sibling;
}

void BTree::insert(int k) {
    if (root->keys.size() == 2 * t - 1) {
        BTreeNode* s = new BTreeNode(t, false);
        s->children.push_back(root);
        s->splitChild(0);
        root = s;
    }
    root->insertNonFull(k);
}

void BTree::remove(int k) {
    root->removeKey(k);
    if (root->keys.empty()) {
        BTreeNode* oldRoot = root;
        if (root->leaf) root = nullptr;
        else root = root->children.front();
        delete oldRoot;
    }
}

BTreeNode* BTree::search(int k) {
    return root->search(k);
}

vector<int> BTree::rangeQuery(int k1, int k2) {
    vector<int> result;
    BTreeNode* current = root;
    queue<BTreeNode*> q;
    q.push(current);

    while (!q.empty()) {
        BTreeNode* node = q.front();
        q.pop();
        for (int key : node->keys) {
            if (key >= k1 && key <= k2) result.push_back(key);
        }
        if (!node->leaf) {
            for (BTreeNode* child : node->children) {
                q.push(child);
            }
        }
    }

    return result;
}

int main() {
    BTree t(3); // B-Tree of minimum degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(15);
    t.insert(30);
    t.insert(25);
    t.insert(40);
    t.insert(50);
    t.insert(35);

    cout << "In-order traversal: ";
    t.traverseInOrder();

    t.remove(6);
    cout << "In-order traversal after deletion of 6: ";
    t.traverseInOrder();

    BTreeNode* result = t.search(15);
    if (result) cout << "15 found in the B-Tree.\n";
    else cout << "15 not found in the B-Tree.\n";

    vector<int> range = t.rangeQuery(10, 30);
    cout << "Range query [10, 30]: ";
    for (int key : range) cout << key << " ";
    cout << endl;

    return 0;
}
