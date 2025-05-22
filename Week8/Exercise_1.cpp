#include<iostream>
#include<vector>
#include<queue>
#include<fstream>

using namespace std;

#define vi vector<int>
#define pii pair<int,int>

const int cs = 1e5 + 7;
const int INF = 1e9 + 7;

int n,s;
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

    cout << "Enter source vertex: ";
    cin >> s;
}

vector<pii> dp;

void Dijkstra(int s) {
    dp.resize(n);
    for (int i = 0;i < n;i++) {
        dp[i] = {INF, i};
    }

    priority_queue<pii,vector<pii>,greater<pii>> q;
    q.push({0,s});
    dp[s] = {0,s};
    while (q.size()) {
        int kc = q.top().first;
        int u = q.top().second;
        q.pop();

        if (kc > dp[u].first) continue;

        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;
            if (dp[v].first > dp[u].first + w) {
                dp[v].first = dp[u].first + w;
                dp[v].second = u;
                q.push({dp[v].first, v});
            }
        }
    }
}

void Trace(int u) {
    vi v;
    while (u != dp[u].second) {
        v.push_back(u);
        u = dp[u].second;
    }
    v.push_back(u);
    for (int i = v.size() - 1;~i;i--) {
        cout << v[i];
        if (i) cout << " -> ";
        else cout << ".";
    }
}

int main() {
    nhap();
    Dijkstra(s);
    for (int i = 0;i < n;i++) {
        if (i == s) continue;
        cout << "The shortest path from " << s << " to " << i << ": ";
        Trace(i);
        cout << endl;
    }
    return 0;
}