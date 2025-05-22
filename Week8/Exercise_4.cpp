#include <iostream>
#include <vector> 
#include <queue>
#include <fstream>
#include <math.h>

using namespace std;

#define vi vector<int>
#define pii pair<int,int>

const int cs = 1e5 + 7;
const int INF = 1e9 + 7;

struct Edge {
    int u,v,w;
    Edge() {}
    Edge(int uu,int vv,int ww) {
        u = uu;
        v = vv;
        w = ww;
    }
    bool operator < (const Edge& other) const {
        return this->w < other.w;
    }
    bool operator > (const Edge& other) const {
        return this->w > other.w;
    }
};

struct DSU {
    vi parent;
    vi sz;
    int n;
    DSU() {}
    void resize(int nn) { 
        n = nn;
        sz.resize(n);
        parent.resize(n);
        for (int i = 0;i < n;i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }
    int Find(int u) {
        if (u == parent[u]) return u;
        return parent[u] = Find(parent[u]);
    }
    bool Joint (int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a,b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int n;
vector<Edge> Canh;
vector<Edge> MST;

void nhap() {
    ifstream input("graph.txt");

    input >> n;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            int x;
            input >> x;
            if (x) Canh.push_back(Edge(min(i,j),max(i,j),x));
        }
    }
}

priority_queue<Edge,vector<Edge>, greater<Edge>> q;

void Solve() {
    DSU D;
    D.resize(n);
    for (auto e : Canh) q.push(e);
    while (q.size()) {
        Edge e = q.top();
        q.pop();
        
        if (MST.size() >= n - 1) break;
        
        if (D.Joint(e.u, e.v)) {
            MST.push_back(e);
        }
    }

    cout << "Edge   Weight" << endl;

    for (auto e : MST) {
        cout << e.u << " - " << e.v << "    " << e.w << endl;
    }
}

int main() {
    nhap();
    Solve();
    return 0;
}