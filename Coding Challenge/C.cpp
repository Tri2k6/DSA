#include <bits/stdc++.h>
using namespace std;

template<class integer>
inline integer to_int(const string& s, size_t* idx = 0, int base = 10) {
    size_t n = s.size(), i = idx ? *idx : 0; bool sign = false; integer x = 0;
    if (s[i] == '-')
        ++i, sign = true;
    function<int(char)> char_to_digit = [&](char c) {
        static const int d[] = {'a'-10,'0'}; 
        return tolower(c)-d[isdigit(c)]; };
    while (i < n)
        x *= base, x += char_to_digit(s[i++]);
    if (idx)
        *idx = i; 
    return sign ? -x : x; }
 
template<class integer>
inline string to_string(integer x, int base = 10) {
    bool sign = false; string s;
    if (x < 0)
        x = -x, sign = true;
    function<char(int)> digit_to_char = [](int d) {
        static const char c[] = {'a'-10,'0'};
        return c[d < 10]+d; };
    do 
        s += digit_to_char(x%base), x /= base;
    while (x > 0); 
    if (sign)
        s += '-';
    reverse(s.begin(),s.end());
    return s; }
 
template<class integer>
inline istream& read(istream& is, integer& x) {
    string s; is >> s, x = to_int<integer>(s); return is; }
 
template<class integer>
inline ostream& write(ostream& os, integer x) { return os << to_string(x); }
 
using  lll =   signed __int128; 
using ulll = unsigned __int128;
 
inline istream& operator>>(istream& is,  lll &x) { return  read(is,x); }
inline istream& operator>>(istream& is, ulll &x) { return  read(is,x); }
inline ostream& operator<<(ostream& os,  lll  x) { return write(os,x); }
inline ostream& operator<<(ostream& os, ulll  x) { return write(os,x); }

#define input cin
#define output cout
#define ll long long 
#define ull unsigned long long
#define pii pair<int,int>
#define endl '\n'
#define all(v) v.begin(),v.end()
#define sorta(v) sort(v.begin(),v.end())
#define mem(a,b) memset(a,b,sizeof(a));
#define GetBit(u) (u & -u)
#define bit(u,i) ((u >> i) & 1)
#define mask(i) (1ll << i)
#define vi vector<int>
#define int128 __int128
#define fi first
#define se second
#define heap_max(a) priority_queue<a>
#define heap_min(a) priority_queue<a, vector<a>, greater <a>>
#define pb push_back
#define eb emplace_back
#define TASK "TASK"

const int cs = 1e6 + 7;
const int mod = 1e9 + 7;
const int INF = mod;
const int maxN = 2e3 + 7;
const int block_size = 320;
const ll oo = 1e18 + 7;

template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        if (x > y) {
            x = y;
            return true;
        } else return false;
    }

template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        if (x < y) {
            x = y;
            return true;
        } else return false;
    }

template<class T>
    T Abs(const T &x) {
        return (x < 0 ? -x : x);
    }

template<class X, class Y>
    void Add(X &x , const Y &y) {
        x += y;
        if (x > mod) x -= mod;
    }

template<class X, class Y>
    void Sub(X &x, const Y &y) {
        x -= y;
        if (x < 0) x += mod;
    }

// 

int n,m;
vi adj[cs];
int a[cs];

void nhap() {
    input >> n;
    for (int i = 0;i < n;i++) {
        input >> a[i];
        m += a[i];
    } 
    for (int i = 0;i < n;i++) {
        if (i == 1) continue;;
        int x;
        input >> x;
        x--;
        adj[i].push_back(x);
        adj[x].push_back(i);
    }
}

int type;

void PhanType() {
    if (n <= 20) return type = 1, void();
    return type = 2, void();
}

struct subTask1 {

    int cnt[21];

    void DFS(int u, int par,int Mask) {

        for (auto v : adj[u]) {
            if (v == par) continue;
            cnt[v] = cnt[u] + bit(Mask, v);
            DFS(v,u, Mask);
        }
    }

    void Solve() {
        int ans = 0;
        for (int Mask = 0;Mask < mask(n);Mask++) {
            int sum = 0;
            for (int i = 0;i < n;i++) {
                sum += bit(Mask,i);
            }
            if (sum != m) continue;
            int tmp = 0;
            for (int i = 0;i < n;i++) {
                mem(cnt, 0);
                DFS(i,0, Mask);
                for (int j = 0;j < n;j++) {
                    if (i != j && (cnt[j] & 1)) {
                        tmp++;
                        break;
                    }
                }
            }
            maximize(ans, tmp);
        }
        output << ans;
    }
};

void Solve() {
    PhanType();
    if (type == 1) {
        subTask1 * T = new subTask1();
        T->Solve();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    if(fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
    }
    int T = 1;
    // input >> T;
    while (T--) {
        nhap();
        Solve();
    }
    return 0;
}