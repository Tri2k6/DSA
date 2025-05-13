#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int val;
    Node * left;
    Node * right;
};

Node* newNode(int data) {
    Node * p = new Node;
    if (!p) return NULL;
    p->val = data;
    p->left = p->right = NULL;
    return p;
}

Node* insert(Node* root,int data) {
    if (!root) {
        root = newNode(data);
        return root;
    } 
    if (root->val == data) return root;
    if (root->val > data) return insert(root->left,data);
    return insert(root->right,data);
}

Node* search(Node* root, int data) {
    if (root == NULL) return NULL;
    if (root->val == data) return root;
    if (data < root->val) return search(root->left, data);
    return search(root->right,data);
}

Node* deleteNode(Node* root, int data) {

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
        cout << u->val << ' ';
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

    int n = 6;
    int * a = new int [6] {8,6,5,7,10,9};

    Node * Root = NULL;

    for (int i = 0;i < n;i++) {
        insert(Root,a[i]);
    }

    NLR(Root);
    cout << endl;
    LNR(Root);
    cout << endl;
    LRN(Root);
    cout << endl;
    deleteNode(Root,8);
    LevelOrder(Root);

    return 0;
}