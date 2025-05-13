#include <iostream>
#include <vector>
using namespace std;

#define input cin
#define output cout
#define ll long long
#define vi vector<int>

const int cs = 10 + 1;

struct Node {
    int n;
    int *a;
    Node() {
        n = 0;
        a = new int[0];
    }
    Node(int nn) {
        n = nn;
        if (n == 0) a = NULL;
        else a = new int[n];
    }
};

int n;
int a[cs];
int x[cs];

vector<Node> res;

void AddNode() {
    vi v;
    
    for (int i = 1;i <= n;i++) {
        if (x[i]) v.push_back(a[i]);
    }

    Node tmp(v.size());

    for (int i = 0;i < v.size();i++) {
        tmp.a[i] = v[i];
    }

    res.push_back(tmp);
}

void BackTrack(int pos) {
    for (int i = 0;i <= 1;i++) {
        x[pos] = i;
        if (pos == n) AddNode();
        else BackTrack(pos + 1);
    }
}

bool cmp(Node a, Node b) {
    if (a.n != b.n) return a.n < b.n;
    for (int i = 0;i < a.n;i++) {
        if (a.a[i] != b.a[i]) return a.a[i] < b.a[i];
    }
    return true;
}

int main() {

    input >> n;
    for (int i = 1;i <= n;i++) input >> a[i];

    for (int i = 1;i <= n;i++) {
        for (int j = i + 1;j <= n;j++) {
            if (a[i] > a[j]) {
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }

    BackTrack(1);

    for (int i = 0;i < res.size();i++) {
        for (int j = i + 1;j < res.size();j++) {
            if (!cmp(res[i], res[j])) {
                // swap n
                int tmp_n = res[i].n;
                res[i].n = res[j].n;
                res[j].n = tmp_n;

                // swap a
                int * tmp_a = res[i].a;
                res[i].a = res[j].a;
                res[j].a = tmp_a;
            }
        }
    }

    for (auto x : res) {
        output << "{";
        for (int i = 0;i < x.n - 1;i++) {
            output << x.a[i] << ",";
        }
        if (x.a != NULL) output << x.a[x.n - 1]; 
        output << "}\n";
    }

    return 0;
}