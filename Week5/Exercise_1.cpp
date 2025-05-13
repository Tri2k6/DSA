#include <iostream> 
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

#define ll long long 
#define vi vector<int> 
#define inputFile "input.txt"
#define outputFile "output.txt"
#define pii pair<int,int> 

typedef struct leader *lref;
typedef struct trailer *tref;

struct leader {
    int val, cnt;
    lref next;
    tref trail;
};

struct trailer {
    lref id;
    tref next;
};

bool nhap(vector<pii> & Canh) {
    ifstream input(inputFile);
    if (!input.is_open()) return false;

    string str;
    while (getline(input,str, ')')) {
        for (int i = 0;i < str.length();i++) {
            if (str[i] < '0' || str[i] > '9') {
                str[i] = ' ';
            }
        }
        stringstream ss(str);
        int x,y;
        ss >> x >> y;
        Canh.push_back({x,y});
    }

    return true;
}

lref addList(lref Head, lref & Tail, int key, int & sz) {
    lref h = Head;
    Tail->val = key;

    while (h->val != key) {
        h = h->next;
    }

    if (h == Tail) {
        Tail = new leader;
        sz++;
        h->cnt = 0;
        h->trail = NULL;
        h->next = Tail;
    }
    return h;
}

void Reset(lref Head, lref Tail) {
    lref p = Head, q;
    tref u,v;

    while (p) {
        q = p->next;
        u = p->trail;

        while (u) {
            v = u->next;
            delete u;
            u = v;
        }

        delete p;
        p = q;
    }
}

void Solve(vector<pii> & Canh) {
    lref Head = new leader;
    lref Tail = Head, p, q;
    tref t;
    int sz = 0, i = 0;
    for (auto e: Canh) {
        int x = e.first;
        int y = e.second;
        p = addList(Head, Tail, x, sz);
        q = addList(Head, Tail, y, sz);
        t = new trailer;
        t->id = q;
        t->next = p->trail;
        p->trail = t;
        q->cnt++;
    } 

    p = Head;
    Head = NULL;

    while (p != Tail) {
        q = p;
        p = p->next;
        if (q->cnt == 0) {
            q->next = Head;
            Head = q;
        }
    }

    vi ans(sz);
    int k = 0;

    q = Head;
    while (q) {
        ans[k++] = q->val;
        sz--;
        t = q->trail;
        q = q->next;
        while (t) {
            p = t->id;
            p->cnt--;
            if (p->cnt == 0) {
                p->next = q;
                q = p;
            }
            t = t->next;
        }
    }
    
    ofstream output(outputFile);
    if (sz) {
        output << -1;
    } else {
        for (int c = 0;c < k;c++) {
            output << ans[c] << ' ';
        }
    }

    Reset(Head, Tail);
    output.close();
}

int main() {
    vector<pii> Canh;
    if (nhap(Canh)) {
        Solve(Canh);
    } else {
        cout << "Error reading file input.txt";
    }
    return 0;
}