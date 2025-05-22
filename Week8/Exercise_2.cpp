#include <iostream>
#include <vector>
#include <fstream>


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

int n,s;
vector<Edge> Canh;

void nhap() {
    ifstream input("graph.txt");
    input >> n;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            int x;
            input >> x;
            if (x) Canh.push_back(Edge(i,j, x));
        }
    }

    cout << "Enter source vertex: ";
    cin >> s;
}

vector<pii> dist;

bool Bellman_ford(int s) {
    dist.assign(n, {INF, -1});
    dist[s] = {0, -1};

    for (int i = 0;i < n - 1;i++) {
        for (auto e : Canh) {
            int u = e.u;
            int v = e.v;
            int w = e.w;
            if (dist[u].first != INF && dist[v].first > dist[u].first + w) {
                dist[v].first = dist[u].first + w;
                dist[v].second = u;
            }
        }
    }

    for (auto e : Canh) {
        int u = e.u, v = e.v, w = e.w;
        if (dist[u].first != INF && dist[v].first > dist[u].first + w) return false;
    }
    return true;
}

void Trace(int u) {
    vi v;
    while (u != -1) {
        v.push_back(u);
        u = dist[u].second;
    }
    for (int i = v.size() - 1;~i;i--) {
        cout << v[i];
        if (i) cout << " -> ";
        else cout << ".";
    }
}

int main() {
    nhap();
    Bellman_ford(s);
    for (int i = 0;i < n;i++) {
        if (i == s) continue;
        cout << "The shortest path from " << s << " to " << i << ": ";
        Trace(i);
        cout << endl;
    }
    return 0;
}