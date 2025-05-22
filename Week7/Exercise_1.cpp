#include <iostream>
#include <queue> 

using namespace std;

enum Color {RED, BLACK};

struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
};

Node* newNode(int data) {
    Node * p = new Node;
    if (!p) return NULL;
    p->key = data;
    p->color = RED;
    p->left = p->right = p->parent = nullptr;
    return p;
}

Node * BST_Insert(Node * root, Node * p) {
    if (!root) return p;

    if (p->key < root->key) {
        root->left = BST_Insert(root->left, p);
        root->left->parent = root;
    } else if (p->key > root->key) {
        root->right = BST_Insert(root->right, p);
        root->right->parent = root;
    }
    return root;
}

void LeftRotation(Node *& root, Node* &p) {
    Node * right_child = p->right;

    p->right = right_child->left;

    if (p->right) {
        p->right->parent = p;
    }

    right_child->parent = p->parent;

    if (!p->parent) root = right_child;
    else if (p == p->parent->left) {
        p->parent->left = right_child;
    } else {
        p->parent->right = right_child;
    }

    right_child->left = p;
    p->parent = right_child;
}

void RightRotation(Node* & root, Node* & p) {
    Node * left_child = p->left;
    p->left = left_child->right;

    if (p->left) p->left->parent = p;

    left_child->parent = p->parent;

    if (!p->parent) root = left_child;
    else if (p == p->parent->left) p->parent->left = left_child;
    else p->parent->right = left_child;

    left_child->right = p;
    p->parent = left_child;
}

void fixViolation(Node*& root, Node*& p) {
    Node * parent_p = NULL;
    Node * grand_parent_p = NULL;

    while ((p != root) && (p->color != BLACK) && (p->parent->color == RED)) {
        parent_p = p->parent;
        grand_parent_p = p->parent->parent;

        if (parent_p == grand_parent_p->left) {
            Node* uncle_pt = grand_parent_p->right;

            if (uncle_pt && uncle_pt->color == RED) {
                grand_parent_p->color = RED;
                parent_p->color = BLACK;
                uncle_pt->color = BLACK;
                p = grand_parent_p;
            } else {
                if (p == parent_p->right) {
                    LeftRotation(root, parent_p);
                    p = parent_p;
                    parent_p = p->parent;
                }

                RightRotation(root, grand_parent_p);
                swap(parent_p->color, grand_parent_p->color);
                p = parent_p;
            }
        } 
        else {
            Node* uncle_pt = grand_parent_p->left;

            if (uncle_pt && uncle_pt->color == RED) {
                grand_parent_p->color = RED;
                parent_p->color = BLACK;
                uncle_pt->color = BLACK;
                p = grand_parent_p;
            } else {
                if (p == parent_p->left) {
                    RightRotation(root, parent_p);
                    p = parent_p;
                    parent_p = p->parent;
                }

                LeftRotation(root, grand_parent_p);
                swap(parent_p->color, grand_parent_p->color);
                p = parent_p;
            }
        }
    }

    root->color = BLACK; 
}

Node *insert(Node* root, int data) {
    Node * p = newNode(data);
    root = BST_Insert(root,p);
    fixViolation(root, p);
    return root;
}

Node* search(Node* root, int data) {
    if (!root || root->key == data) return root;
    if (data < root->key) return search(root->left, data);
    return search(root->right, data);
}

Node* FindMin(Node * root) {
    if (!root) return NULL;
    if (!root->left && !root->right) return root;
    return FindMin(root->left);
}

bool isOnLeft(Node* root) {
    return root == root->parent->left;
}

void replaceNode(Node*& root, Node* u, Node* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
}

Node* sibling(Node* node) {
    if (!node->parent) return nullptr;
    if (node == node->parent->left)
        return node->parent->right;
    return node->parent->left;
}

void fixDoubleBlack(Node*& root, Node* x) {
    if (x == root) return;

    Node* sib = sibling(x);
    Node* parent = x->parent;

    if (!sib) {
        fixDoubleBlack(root, parent);
    } else {
        if (sib->color == RED) {
            parent->color = RED;
            sib->color = BLACK;
            if (sib == parent->left) RightRotation(root, parent);
            else LeftRotation(root, parent);
            fixDoubleBlack(root, x);
        } else {
            if ((sib->left && sib->left->color == RED) || (sib->right && sib->right->color == RED)) {
                if (sib->left && sib->left->color == RED) {
                    if (sib == parent->left) {
                        sib->left->color = sib->color;
                        sib->color = parent->color;
                        RightRotation(root, parent);
                    } else {
                        sib->left->color = parent->color;
                        RightRotation(root, sib);
                        LeftRotation(root, parent);
                    }
                } else {
                    if (sib == parent->left) {
                        sib->right->color = parent->color;
                        LeftRotation(root, sib);
                        RightRotation(root, parent);
                    } else {
                        sib->right->color = sib->color;
                        sib->color = parent->color;
                        LeftRotation(root, parent);
                    }
                }
                parent->color = BLACK;
            } else {
                sib->color = RED;
                if (parent->color == BLACK)
                    fixDoubleBlack(root, parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}

Node* deleteBST(Node* root, Node* v) {
    Node* u = FindMin(v->right);
    v->key = u->key;
    return u;
}

Node* deleteNodeHelper(Node*& root, Node* v) {
    Node* u = v;
    Node* x = nullptr;
    Color originalColor = u->color;

    if (!v->left) {
        x = v->right;
        replaceNode(root, v, v->right);
    } else if (!v->right) {
        x = v->left;
        replaceNode(root, v, v->left);
    } else {
        u = FindMin(v->right);
        originalColor = u->color;
        x = u->right;

        if (u->parent != v) {
            replaceNode(root, u, u->right);
            u->right = v->right;
            if (u->right) u->right->parent = u;
        }

        replaceNode(root, v, u);
        u->left = v->left;
        if (u->left) u->left->parent = u;
        u->color = v->color;
    }

    delete v;

    if (originalColor == BLACK) {
        if (x)
            fixDoubleBlack(root, x);
        else {
            x = newNode(0);
            x->color = BLACK;
            x->parent = u->parent;
            fixDoubleBlack(root, x);
            replaceNode(root, x, nullptr);
            delete x;
        }
    }

    return root;
}

Node* deleteNode(Node* root, int data) {
    Node* v = search(root, data);
    if (!v) return root;

    return deleteNodeHelper(root, v);
}

void LevelOrder(Node* root) {
    queue<Node*> q;
    q.push(root);
    while (q.size()) {
        Node * u = q.front();
        q.pop();
    
        cout << u->key << ' ' << u->color << endl;

        if (u->left) q.push(u->left);
        if (u->right) q.push(u->right);
    }
    cout << endl;
}

int main() {

    return 0;

}