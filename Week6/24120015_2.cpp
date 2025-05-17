#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int key;
    Node * left;
    Node * right;
    int height;
};

int max(int a, int b) {
    return (a >= b) ? a : b;
}

Node* newNode(int data) {
    Node * p = new Node;
    if (!p) return NULL;
    p->key = data;
    p->height = 1;
    p->left = p->right = NULL;
    return p;
}

int Get_height(Node * root) {
    return root ? root->height : 0;
}

int get_Balance(Node * root) {
    return root ? Get_height(root->left) - Get_height(root->right): 0;
}

Node * rightRotate(Node * y) {
    Node* x = y->left;
    Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;

    y->height = max(Get_height(y->left), Get_height((y->right))) + 1;
    x->height = max(Get_height(x->left), Get_height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node * x) {
    Node * y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(Get_height(x->left), Get_height(x->right)) + 1;
    y->height = max(Get_height(y->left), Get_height(y->right)) + 1;
    
    return y;
}

Node* insertNode(Node* root,int data) {
    if (!root) return newNode(data);

    if (data < root->key) {
        root->left = insertNode(root->left, data);
    } else if (data > root->key) {
        root->right = insertNode(root->right, data);
    } else return root;

    root->height = 1 + max(Get_height(root->left), Get_height(root->right));
    int balance = get_Balance(root); 

    if (balance > 1 && data < root->left->key) {
        return rightRotate(root);
    }
    if (balance < -1 && data > root->right->key) {
        return leftRotate(root);
    }
    if (balance > 1 && data > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && data < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

Node* searchNode(Node * root, int data) {
    if (!root) return NULL;
    if (root->key == data) return root;
    if (root->key < data) return searchNode(root->right, data);
    return searchNode(root->left, data);
}

Node* maxNode(Node* root) {
    if (!root) return NULL;
    if (!root->left && !root->right) return root;
    return maxNode(root->right);
}

Node* deleteNode(Node* root, int data) {
    if (!root) return root;
    if (data < root->key) {
        root->left = deleteNode(root->left,data);
    } else if (data > root->key) {
        root->right = deleteNode(root->right, data);
    } else {
        if (!root->left || !root->right) {
            Node * tmp = root->left ? root->left: root->right;
            delete root;
            return tmp;
        }

        Node * tmp = maxNode(root->left);
        root->key = tmp->key;
        root->left = deleteNode(root->left, tmp->key);
    }

    if (!root) return root;
    
    root->height = 1 + max(Get_height(root->left), Get_height(root->right));
    int balance = get_Balance(root);

    if (balance > 1 && get_Balance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && get_Balance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && get_Balance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && get_Balance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void NLR(Node * root) {
    if (!root) return;
    cout << root->key << ' ';
    NLR(root->left);
    NLR(root->right);
}

void LNR(Node* root) {
    if (!root) return;
    LNR(root->left);
    cout << root->key << ' ';
    LNR(root->right);
}

void LRN(Node * root) {
    if (!root) return;
    LRN(root->left);
    LRN(root->right);
    cout << root->key << ' ';
}

void LevelOrder(Node* root) {
    queue<Node*> q;
    q.push(root);
    while (q.size()) {
        Node * u = q.front();
        q.pop();
        
        cout << u->key << " ";

        if (u->left) {
            q.push(u->left);
            // cout << u->left->key << ' ';
        }
        if (u->right) {
            q.push(u->right);
            // cout << u->right->key << ' ';
        }
        // cout << endl;
    }
}

bool isFull(Node* root) {
    if (!root) return true;
    if (!root->left && !root->right) return true;
    int LeftChild = (root->left) ? 1 : 0;
    int RightChild = (root->right) ? 1 : 0; 
    if ((LeftChild + RightChild) & 1) return false;
    return (1 && isFull(root->left) && isFull(root->right));
}

bool isComplete(Node* root) {
    if (!root) return true;

    queue<Node*> q;
    q.push(root);
    
    bool ans = 0;

    while (q.size()) {
        Node * u = q.front(); 
        q.pop();

        if (u->left) {
            if (ans) return false;
            q.push(u->left);
        } else ans = true;

        if (u->right) {
            if (ans) return false;
            q.push(u->right);
        } else ans = true;
    }
    return true;
}

int GetDepth(Node * root) {
    int ans = 0;
    while (root) {
        ans++;
        root = root->left;
    }
    return ans;
}

bool isPerfect1(Node* root,int depth, int level = 0) {
    if (!root) return true;
    if (!root->left && !root->right) return depth == level + 1;
    if (!root->left || !root->right) return false;

    return isPerfect1(root->left, depth, level + 1) && isPerfect1(root->right, depth, level + 1);
}

bool isPerfect(Node* root) {
    int depth = GetDepth(root);
    return isPerfect1(root,depth);
}


int findCommonAncestor(Node* root, int x, int y) {
    if (!root) return -1;
    if (x < root->key && y < root->key) return findCommonAncestor(root->left,x,y);
    if (x > root->key && y > root->key) return findCommonAncestor(root->right, x,y);
    return (searchNode(root,x) && searchNode(root,y)) ? root->key : -1;
}

void printSpecialNodes(Node* root) {
    if (!root) return;
    printSpecialNodes(root->left);
    if (root->left && root->right && root->right->key % root->left->key == 0) cout << root->key << ' ';
    printSpecialNodes(root->right);
}

int main() {

    int n = 8;
    int * a = new int[8] {20, 10, 40, 4, 16, 8, 24, 48};

    Node * root = NULL;

    for (int i = 0;i < n;i++) {
        root = insertNode(root, a[i]);
    }

    cout << "NLR: "; NLR(root); cout << endl;
    cout << "LNR: "; LNR(root); cout << endl;
    cout << "LRN: "; LRN(root); cout << endl;
    cout << "Level Order: "; LevelOrder(root); cout << endl;

    root = deleteNode(root, 10);

    cout << "Level Order after deletion: "; LevelOrder(root); cout << endl;

    cout << "isFull: " << (isFull(root) ? "YES" : "NO") << endl;
    cout << "isComplete: " << (isComplete(root) ? "YES" : "NO") << endl;
    cout << "isPerfect: " << (isPerfect(root) ? "YES" : "NO") << endl;
    int x = 24, y = 4;
    cout << "The Least Common Ancesstor of " << x << " and " << y << ": " << findCommonAncestor(root, x,y) << endl; 
    cout << "The special nodes: "; printSpecialNodes(root);
    return 0;
}