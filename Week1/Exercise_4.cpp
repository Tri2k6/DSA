#include <iostream> 

using namespace std;

#define input cin
#define output cout

struct Node {
    int data;
    Node * next;
    Node() {
        next = NULL;
    }
    Node(int d) {
        data = d;
        next = NULL;
    }
};

void Traversal_Nodes(Node * Head) {
    for (auto p = Head; p; p = p->next) {
        output << p->data << ' ';
    }
    output << endl;
}

int Count_Nodes(Node * Head) {
    int cnt = 0;
    for (auto p = Head; p; p = p->next) {
        cnt++;
    }
    return cnt;
}

bool isEmpty(Node * Head) {
    return Head == NULL;
}

void AddHead(Node * & Head,Node * p) {
    if (isEmpty(Head)) Head = p;
    else {
        p->next = Head;
        Head = p;
    }
}

Node * FindTail(Node * Head) {
    Node * ans = NULL;
    for (auto p = Head; p; p = p->next) {
        if (p) ans = p;
    }
    return ans;
}

void AddTail(Node * & Head, Node * p) {
    if (isEmpty(Head)) return Head = p, void();
    Node * Tail = FindTail(Head);
    Tail->next = p;
}

bool RemoveHead(Node * &Head) {
    if (isEmpty(Head)) return false;
    Node * p = Head;
    Head = Head->next;
    delete p;
    return true;
}

Node * Find_nth_Node(Node * Head,int k) {
    int idx = 0;
    for (auto p = Head;p;p = p -> next) {
        idx++;
        if (idx == k) return p;
    }
    return NULL;
}

bool RemoveTail(Node * &Head) {
    if (isEmpty(Head)) return false;
    int n = Count_Nodes(Head);
    if (n == 1) {
        Head = NULL;
        return true;
    }

    Node * preTail = Find_nth_Node(Head, n - 1);
    Node * Tail = preTail->next;
    preTail->next = NULL;
    delete Tail;
    return true;
}

void removeNode(Node * &pre, Node * &p) {
    Node * ptrNext = p->next;
    pre->next = ptrNext;
    delete p;
}

void RemoveDuplicate(Node *& Head) {
    Node * cur = Head;
    
    while (cur && cur->next) {
        Node * runner = cur;

        while (runner->next) {
            if (cur->data == runner->next->data) {
                Node * tmp = runner->next;
                runner->next = runner->next->next;
                delete tmp;
            } else {
                runner = runner->next;
            }
        }
        cur = cur->next;
    }
}



int main() {
    
    // Node * Head = NULL;

    // AddHead(Head, new Node(2));
    // AddTail(Head, new Node(1));
    // AddTail(Head, new Node(3));
    // AddTail(Head, new Node(3));

    // RemoveDuplicate(Head);
    // Traversal_Nodes(Head);

    return 0;
}