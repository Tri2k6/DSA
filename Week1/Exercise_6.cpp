#include <iostream>
using namespace std;

struct Node {
    int data;
    Node * next;

    Node() {
        data = 0;
        next = NULL;
    }
};

struct Queue {
    int n;
    Node * ptrHead;
    Node * ptrTail;

    Queue() {
        n = 0;
        ptrHead = ptrTail = NULL;
    }

    bool isEmpty() {
        return n == 0;
    }

    void enqueue(int val) {
        Node * p = new Node();
        p->data = val;

        if (isEmpty()) {
            ptrHead = ptrTail = p;
            n++;
        } else {
            ptrTail->next = p;
            ptrTail = p;
            n++;
        }
    }

    bool dequeue() {
        if (isEmpty()) return false;
        if (n == 1) {
            Node * p = ptrHead;
            ptrHead = ptrTail = NULL;
            delete p;
        } else {
            Node * p = ptrHead;
            ptrHead = ptrHead -> next;  
            delete p;
        }
        return true;
    }

    int front() {
        return ptrHead->data;
    }
};


int main() {

    return 0;
}