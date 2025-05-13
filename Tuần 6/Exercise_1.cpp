#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int val;
    Node * left, right;
};

Node* newNode(int data) {
    Node * p = new Node;
    if (!p) return NULL;
    p->val = data;
    p->left = p->right = NULL;
    return p;
}

Node* insert(Node* root,int data) {
    Node *tmp = newNode(data);
    Node* p = root;
    while (p) {
        if (p->val == data) return p;
        if (data < p->val) {
            if (p->left) p = p->left;
            else {
                p->left = tmp;
                return tmp;
            }
        }

    }
    return tmp;
}

Node* search(Node* root, int data) {
    if (root == NULL) return NULL;
    if (root->val == data) return Node;
    if (data < root->val) return search(root->left, data);
    return search(root->right,data);
}

Node* delete(Node* root, int data) {

}

void NLR(Node* root) {
    if (!root) return;
    cout << root->val << ' ';
    NLR(root->left);
    NLR(root->right);
}

 void LNR(Node* root) {
    if (!root) return;
    LNR(root->left);
    cout << root->val << ' ';
    LNR(root->right);
 }

 void LRN(Node* root) {
    if (!root) return;
    LRN(root->left);
    LRN(root->right);
    cout << root->val << ' ';
 }

 void LevelOrder(Node* root) {
    queue<Node*> q;
    q.push(root);
    while (q.size()) {
        Node * u = q.front();
        q.pop();
        cout << u->val << ' ';s
        if (u->left) q.push(u->left);
        if (u->right) q.push(u->right);
    }
 }

 int height(Node* root) {
    if (!root) return 0;
    return max(height(root->left), height(root->right)) + 1;
 }

int countNode(Node* root) {
    if (!root) return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int countInternal(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 0;
    return 1 + countInternal(root->left) + countInternal(root->right);
}

int sumNode(Node* root) {
    if (!root) return 0;
    return root->val + sumNode(root->left) + sumNode(root->right);
}

int countLeaf(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

int countLess(Node* root, int x) {
    if (!root) return;
    if (root->val < x) return countNode(root->left) + countLess(root->right, x);
    return countLess(root->left,x);
}

int countGreater(Node* root,int x) {
    if (!root) return;
    if (root->val > x) return countNode(root->right) + countGreater(root->left, x);
    return countGreater(root->right, x);
}

int main() {

    n = 6;
    int * a = {8,6,5,7,10,9};

    Node * Root = NULL;

    for (int i = 0;i < n;i++) {
        insert(root,a[i]);
    }

    NLR(root);
    cout << endl;
    LNR(root);
    cout << endl;
    LRN(root);
    cout << endl;
    delete(root,8);
    LevelOrder(root);

    return 0;
}