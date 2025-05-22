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
};

int n;
vector<pii> adj[cs];

void nhap() {
    ifstream input("graph.txt");
    input >> n;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            int x;
            input >> x;
            if (x) {
                adj[i].push_back({j,x});
            }
        }
    }
}

void Solve() {
    vi visited(n, 0);
    vector<pii> parent(n,{-1, 1e9});
    priority_queue<pii, vector<pii>, greater<pii>> q;
    
    int ans = 0;
    q.push({0,0});
    parent[0].second = 0;

    vector<Edge> MST;

    while (q.size()) {
        int weight = q.top().first;
        int u = q.top().second;
        q.pop();

        if (visited[u]) continue;
        visited[u] = true;
        ans += weight;

        if (parent[u].first >= 0) MST.push_back(Edge(parent[u].first, u, parent[u].second));

        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;
            if (!visited[v] && w < parent[v].second) {
                parent[v].second = w;
                parent[v].first = u;
                q.push({w,v});
            }
        }

    }
    cout << "Edge    Weight" << endl;
    for (auto e: MST) {
        cout << e.u << " - " << e.v << "    " << e.w << endl; 
    }
}

int main() {
    nhap();
    Solve();
    return 0;
}