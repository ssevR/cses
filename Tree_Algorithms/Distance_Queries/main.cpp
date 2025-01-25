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
    vector<vector<int> > g(n);
    vector<int> lvl(n);
    vector<vector<int> > up(n + 1, vector<int>(19));
 
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
        /*
        int p;
        cin >> p;
        --p;
        up[i][0] = p;
        lvl[i] = lvl[p] + 1;
        */
    }
    auto dfs = [&](int v, int p, auto&& dfs) -> void {
        for (auto u : g[v]) {
            if (u == p)
                continue;
            lvl[u] = lvl[v] + 1;
            up[u][0] = v;
            dfs(u, v, dfs);
        }
    };
    dfs(0, -1, dfs);
 
    up[0][0] = n;
    up[n][0] = n;
 
    for (int j = 1; j < 19; ++j)
        for (int i = 0; i < n + 1; ++i)
            up[i][j] = up[up[i][j - 1]][j - 1];
 
    while(q--) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        if (lvl[u] > lvl[v])
            swap(v, u);
 
        int k = lvl[v] - lvl[u];
        int res = k;
        for (int i = 0; i < 19; ++i) {
            if (k & (1 << i))
                v = up[v][i];
        }
        if (v == u) {
            cout << res << '\n';
            continue;
        }
        for (int i = 18; i >= 0; --i) {
            if (up[v][i] != up[u][i]) {
                res += (1 << (i + 1));
                v = up[v][i];
                u = up[u][i];
            }
        }
        cout << res + 2 << '\n';
    }

    return 0;
}
