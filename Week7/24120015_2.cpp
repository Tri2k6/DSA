#include <iostream>
#include <queue>

using namespace std;

const int MAX = 3; 
const int MIN = (MAX + 1) / 2;

struct Node {
    int keys[MAX];              
    Node* children[MAX + 1];   
    int numKeys;              
    bool isLeaf;           

    Node(bool leaf) {
        numKeys = 0;
        isLeaf = leaf;
        for (int i = 0; i < MAX + 1; i++)
            children[i] = nullptr;
    }
};

Node* newNode(bool isLeaf) {
    Node* node = new Node(isLeaf);
    return node;
}

void splitChild(Node* x, int i, Node* y) {
    Node* z = newNode(y->isLeaf);
    z->numKeys = MAX / 2;  

    for (int j = 0; j < z->numKeys; j++)
        z->keys[j] = y->keys[j + 1 + z->numKeys];

    if (!y->isLeaf) {
        for (int j = 0; j <= z->numKeys; j++)
            z->children[j] = y->children[j + 1 + z->numKeys];
    }

    y->numKeys = MAX / 2;  

    for (int j = x->numKeys; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;

    for (int j = x->numKeys - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[MAX / 2];
    x->numKeys++;
}

void insertNonFull(Node* x, int data) {
    int i = x->numKeys - 1;

    if (x->isLeaf) {
        while (i >= 0 && x->keys[i] > data) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = data;
        x->numKeys++;
    } else {
        while (i >= 0 && x->keys[i] > data)
            i--;
        i++;

        if (x->children[i]->numKeys == MAX) {
            splitChild(x, i, x->children[i]);
            if (x->keys[i] < data)
                i++;
        }
        insertNonFull(x->children[i], data);
    }
}

Node* insert(Node* root, int data) {
    if (root == nullptr) {
        root = newNode(true);
        root->keys[0] = data;
        root->numKeys = 1;
        return root;
    }

    if (root->numKeys == MAX) {
        Node* s = newNode(false);
        s->children[0] = root;
        splitChild(s, 0, root);

        int i = 0;
        if (s->keys[0] < data)
            i++;
        insertNonFull(s->children[i], data);
        return s;
    } else {
        insertNonFull(root, data);
        return root;
    }
}

Node* search(Node* root, int data) {
    if (root == nullptr)
        return nullptr;

    int i = 0;
    while (i < root->numKeys && data > root->keys[i])
        i++;

    if (i < root->numKeys && root->keys[i] == data)
        return root;

    if (root->isLeaf)
        return nullptr;

    return search(root->children[i], data);
}


int getSucc(Node* node, int idx) {
    Node* cur = node->children[idx + 1];
    while (!cur->isLeaf)
        cur = cur->children[0];
    return cur->keys[0];
}

int getPred(Node* node, int idx) {
    Node* cur = node->children[idx];
    while (!cur->isLeaf)
        cur = cur->children[cur->numKeys];
    return cur->keys[cur->numKeys - 1];
}

void removeFromLeaf(Node* node, int idx) {
    for (int i = idx + 1; i < node->numKeys; i++)
        node->keys[i - 1] = node->keys[i];
    node->numKeys--;
}

void removeFromNonLeaf(Node* node, int idx);

void fill(Node* node, int idx);

void borrowFromPrev(Node* node, int idx);

void borrowFromNext(Node* node, int idx);

void merge(Node* node, int idx);

Node* deleteNode(Node* node, int data) {
    if (node == nullptr) return node;

    int idx = 0;
    while (idx < node->numKeys && node->keys[idx] < data)
        ++idx;

    if (idx < node->numKeys && node->keys[idx] == data) {
        if (node->isLeaf) {
            removeFromLeaf(node, idx);
        } else {
            removeFromNonLeaf(node, idx);
        }
    } else {
        if (node->isLeaf) {
            return node;
        }
        bool flag = (idx == node->numKeys);

        if (node->children[idx]->numKeys < MIN)
            fill(node, idx);

        if (flag && idx > node->numKeys)
            node->children[idx - 1] = deleteNode(node->children[idx - 1], data);
        else
            node->children[idx] = deleteNode(node->children[idx], data);
    }
    return node;
}

void removeFromNonLeaf(Node* node, int idx) {
    int k = node->keys[idx];

    if (node->children[idx]->numKeys >= MIN) {
        int pred = getPred(node, idx);
        node->keys[idx] = pred;
        node->children[idx] = deleteNode(node->children[idx], pred);
    } else if (node->children[idx + 1]->numKeys >= MIN) {
        int succ = getSucc(node, idx);
        node->keys[idx] = succ;
        node->children[idx + 1] = deleteNode(node->children[idx + 1], succ);
    } else {
        merge(node, idx);
        node->children[idx] = deleteNode(node->children[idx], k);
    }
}

void fill(Node* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->numKeys >= MIN)
        borrowFromPrev(node, idx);
    else if (idx != node->numKeys && node->children[idx + 1]->numKeys >= MIN)
        borrowFromNext(node, idx);
    else {
        if (idx != node->numKeys)
            merge(node, idx);
        else
            merge(node, idx - 1);
    }
}

void borrowFromPrev(Node* node, int idx) {
    Node* child = node->children[idx];
    Node* sibling = node->children[idx - 1];

    for (int i = child->numKeys - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = node->keys[idx - 1];

    if (!child->isLeaf)
        child->children[0] = sibling->children[sibling->numKeys];

    node->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];

    child->numKeys += 1;
    sibling->numKeys -= 1;
}

void borrowFromNext(Node* node, int idx) {
    Node* child = node->children[idx];
    Node* sibling = node->children[idx + 1];

    child->keys[child->numKeys] = node->keys[idx];

    if (!(child->isLeaf))
        child->children[child->numKeys + 1] = sibling->children[0];

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->numKeys; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->numKeys; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->numKeys += 1;
    sibling->numKeys -= 1;
}

void merge(Node* node, int idx) {
    Node* child = node->children[idx];
    Node* sibling = node->children[idx + 1];

    child->keys[MIN - 1] = node->keys[idx];

    for (int i = 0; i < sibling->numKeys; ++i)
        child->keys[i + MIN] = sibling->keys[i];

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->numKeys; ++i)
            child->children[i + MIN] = sibling->children[i];
    }

    for (int i = idx + 1; i < node->numKeys; ++i)
        node->keys[i - 1] = node->keys[i];

    for (int i = idx + 2; i <= node->numKeys; ++i)
        node->children[i - 1] = node->children[i];

    child->numKeys += sibling->numKeys + 1;
    node->numKeys--;

    delete sibling;
}

void NLR(Node* root) {
    if (root == nullptr) return;
    for (int i = 0; i < root->numKeys; i++)
        cout << root->keys[i] << " ";

    for (int i = 0; i <= root->numKeys; i++)
        NLR(root->children[i]);
}

void LNR(Node* root) {
    if (root == nullptr) return;
    for (int i = 0; i < root->numKeys; i++) {
        LNR(root->children[i]);
        cout << root->keys[i] << " ";
    }
    LNR(root->children[root->numKeys]);
}

void LRN(Node* root) {
    if (root == nullptr) return;
    for (int i = 0; i <= root->numKeys; i++)
        LRN(root->children[i]);
    for (int i = 0; i < root->numKeys; i++)
        cout << root->keys[i] << " ";
}

void LevelOrder(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        for (int i = 0; i < node->numKeys; i++)
            cout << node->keys[i] << " ";
        if (!node->isLeaf) {
            for (int i = 0; i <= node->numKeys; i++)
                if (node->children[i] != nullptr)
                    q.push(node->children[i]);
        }
    }
}

int main() {

    return 0;
}
