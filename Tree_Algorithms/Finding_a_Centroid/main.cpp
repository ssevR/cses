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
 
int find_centroid(vector<vector<int> >& g) {
    int n = g.size();
    if (n == 1)
        return 0;
 
    vector<int> sz(n);
    auto dfs = [&](int v, int p, auto&& dfs) -> int {
        sz[v] = 1;
 
        int mx = 0;
 
        for (auto u : g[v]) {
            if (u == p)
                continue;
            auto tmp = dfs(u, v, dfs);
            sz[v] += sz[u];
            if (tmp != -1) {
                return tmp;
            }
            mx = max(mx, sz[u]);
        }
        if (mx <= n/2 && n - sz[v] <= n/2) {
            return v;
        }
        return -1;
    };
    return dfs(0, -1, dfs);
}
 
int main() {
    IOS;
    int n;
    cin >> n;
    vector<vector<int> > g(n);
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    cout << find_centroid(g) + 1 << '\n';

    return 0;
}
