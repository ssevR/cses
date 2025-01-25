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
 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const int MOD = 1e9 + 7;
 
vector<vector<int> > g;
vector<int> used;
 
 
pii dfs(int v) {
    used[v] = 1;
    pii res = {1, g[v].size()};
    for (auto u : g[v]) {
        if (!used[u]) {
            auto tmp = dfs(u);
            res.fi += tmp.fi;
            res.se += tmp.se;
        }
    }
    return res;
}
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    g.resize(n);
    used.resize(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    int deg2 = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            auto x = dfs(i);
            deg2 += x.se / 2 - x.fi + 1;
        }
    }
    int res = 1;
    for (int i = 0; i < deg2; ++i) {
        res = res * 2 % MOD;
    }
    cout << res << '\n';
}
