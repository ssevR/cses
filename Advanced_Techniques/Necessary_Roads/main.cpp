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
 
// find all bridges of undirected graph with no multiedges
 
vector<pair<int, int> > find_bridges (vector<vector<int> >& g) {
    int n = g.size();
    vector<int> tin(n), low(n), used(n);
    vector<pair<int, int> > res;
    int timer = 0;
 
    auto dfs = [&](int v, int p, auto&& dfs) -> void {
        used[v] = 1;
        tin[v] = low[v] = ++timer;
        for (auto u : g[v]) {
            if (u == p)
                continue;
            else if (used[u]) {
                low[v] = min(low[v], tin[u]);
            }
            else {
                dfs(u, v, dfs);
                if (low[u] > tin[v]) {
                    res.emplace_back(v, u);
                }
                low[v] = min(low[v], low[u]);
            }
        }
    };
    for (int i = 0; i < n; ++i) 
        if (!used[i]) dfs(i, -1, dfs);
    return res;
}
int main() {
 
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    auto res = find_bridges(g);
    cout << res.size() << '\n';
    for (auto [v, u] : res)
        cout << v + 1 << ' ' << u + 1 << '\n';
}
