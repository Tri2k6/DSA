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

struct Stack {
    int n;
    Node * ptrTop;
    Stack() {
        n = 0;
        ptrTop = NULL;
    }
    
    bool isEmpty() {
        return n == 0;
    }
    
    void push(int val) {
        Node * p = new Node();
        p->data = val;

        p->next = ptrTop;
        ptrTop = p;
        n++;
    } 

    bool pop() {
        if (this->isEmpty()) return false;

        Node * p = ptrTop;
        ptrTop = ptrTop->next;
        n--;
        delete p;
        return true;
    } 
    
    int top() {
        return ptrTop->data;
    }
};


int main() {

    return 0;
}