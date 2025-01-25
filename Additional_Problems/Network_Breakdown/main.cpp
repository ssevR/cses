#pragma GCC optimize("O3")
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define IOS ios::sync_with_stdio(false); cin.tie(0)
#define ll long long
#define ld long double
#define mp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define fi first
#define se second
 
 
const int N = 1e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int parent[N];
 
int find_set(int a) {
    if (a == parent[a])
        return a;
    return parent[a] = find_set(parent[a]);
}
 
int union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        parent[b] = a;
        return 1;
    }
    return 0;
}
 
 
struct pii_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(pair<uint32_t, uint32_t> a) const {
        uint64_t x = (uint64_t(a.fi) << 32) + uint64_t(a.se);
 
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
 
int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    iota(parent, parent + n, 0);
    unordered_map<pii, int, pii_hash> edges;
    vector<pii> queries(k);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        if (v > u)
            swap(v, u);
        edges[mp(v, u)] = 1;
    }
    for (int i = 0; i < k; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        if (v > u)
            swap(v, u);
        edges[mp(v, u)] = 0;
        queries[i] = {v, u};
    }
    int cnt = n;
    for (auto e : edges) {
        if (e.se)
            cnt -= union_sets(e.fi.fi, e.fi.se);
    }
    vector<int> res(k);
    for (int i = k - 1; i >= 0; --i) {
        res[i] = cnt;
        auto [v, u] = queries[i];
        if (edges[mp(v, u)] == 0) {
            edges[mp(v, u)] = 1;
            cnt -= union_sets(v, u);
        }
    }
    for (auto x : res)
        cout << x << ' ';
    cout << '\n';

    return 0;
}
