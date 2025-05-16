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
    Node * p = root;
    Node * tmp = newNode(data);
    while (p) {
        if (p->val == data) break;
        if (data < p->val) {
            if (!p->left) {
                p->left = tmp;
            }
            p = p->left;
        } else {
            if (!p->right) {
                p->right = tmp;
                break;
            }
            p = p->right;
        }

    }
    return root;
}

Node* search(Node* root, int data) {
    if (root == NULL) return NULL;
    if (root->val == data) return root;
    if (data < root->val) return search(root->left, data);
    return search(root->right,data);
}

Node* FindMax(Node * Root) {
    if (!Root) return NULL;
    if (!Root->left && !Root->right) return Root;
    return FindMax(Root->right);
} 

Node* deleteNode(Node* root, int data) {
    if (!root) return NULL;
    if (data < root->val) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->val) {
        root->right = deleteNode(root->right,data);
    } else {
        if (!root->left && !root->right) {
            delete root;
            return NULL;
        } else if (!root->left) {
            Node * tmp = root->right;
            delete root;
            return tmp;
        } else if (!root->right) {
            Node * tmp = root->left;
            delete root;
            return tmp;
        } else {
            Node * tmp = FindMax(root->left);
            root->val = tmp->val;
            root->left = deleteNode(root->left, tmp->val);
        }
    }
    return root;
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
    queue<pair<Node*, int>> q;
    q.push({root,0});
    while (q.size()) {
        Node * u = q.front().first;
        int level = q.front().second;
        q.pop();
        cout << u->val << ' ';
        if (u->left) q.push({u->left,level + 1});
        if (u->right) q.push({u->right,level + 1});
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
    if (!root) return 0;
    if (root->val < x) return 1 + countLess(root->left,x) + countLess(root->right, x);
    return countLess(root->left,x);
}

int countGreater(Node* root,int x) {
    if (!root) return 0;
    if (root->val > x) return 1 + countGreater(root->right,x) + countGreater(root->left, x);
    return countGreater(root->right, x);
}

int main() {

    int n = 6;
    int * a = new int [6] {8,6,5,7,10,9};

    Node * Root = NULL;

    for (int i = 0;i < n;i++) {
        Root = insert(Root,a[i]);
    }

    int x = 7;

    cout << "Pre-order: ";
    NLR(Root);
    cout << endl;
    cout << "In-order: ";
    LNR(Root);
    cout << endl;
    cout << "Post-order: ";
    LRN(Root);
    cout << endl;
    cout << "Level-order: "; LevelOrder(Root); cout << endl;
    Root = deleteNode(Root,8);
    cout << "Level-order after deletion: "; LevelOrder(Root); cout << endl;
    cout << "Height: " << height(Root) << endl;
    cout << "Total nodes: " << countNode(Root) << endl;
    cout << "Internal nodes: " << countInternal(Root) << endl;
    cout << "Sum of all nodes: " << sumNode(Root) << endl;
    cout << "Leaf Node: " << countLeaf(Root) << endl;
    cout << "Nodes less than " << x << ": "  << countLess(Root,7) << endl;
    cout << "Nodes greater than " << x << ": " << countGreater(Root,7) << endl;

    return 0;
}