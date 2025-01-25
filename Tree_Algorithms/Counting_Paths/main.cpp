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
 
 
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<int> lvl(n);
    vector<vector<int> > up(n + 1, vector<int>(19));
    vector<vector<int> > g(n);
 
    for (int i = 1; i < n; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    up[0][0] = n;
    up[n][0] = n;
    auto dfs1 = [&](int v, auto&& dfs1) -> void {
        for (auto u : g[v]) 
            if (u != up[v][0]) {
                up[u][0] = v;
                lvl[u] = lvl[v] + 1;
                dfs1(u, dfs1);
            }
    };
    dfs1(0, dfs1);
 
 
    for (int j = 1; j < 19; ++j)
        for (int i = 0; i < n + 1; ++i)
            up[i][j] = up[up[i][j - 1]][j - 1];
 
    vector<int> f(n);
    while(q--) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        ++f[v], ++f[u];
 
        if (lvl[u] > lvl[v])
            swap(v, u);
 
        int k = lvl[v] - lvl[u];
        for (int i = 0; i < 19; ++i) {
            if (k & (1 << i))
                v = up[v][i];
        }
        int lca;
        if (v == u) {
            lca = v;
        }
        else {
            for (int i = 18; i >= 0; --i) {
                if (up[v][i] != up[u][i]) {
                    v = up[v][i];
                    u = up[u][i];
                }
            }
            lca = up[v][0];
        }
        --f[lca];
        if (lca != 0)
            --f[up[lca][0]];
    }
 
    auto dfs = [&](int v, auto&& dfs) -> void {
        for (auto u : g[v]) 
            if (u != up[v][0]) {
                dfs(u, dfs);
                f[v] += f[u];
            }
    };
    dfs(0, dfs);
    for (int i = 0; i < n; ++i)
        cout << f[i] << ' ';
    cout << '\n';

    return 0;
}
