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
const int M = 19;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
int parent[N], lvl[N], used[N];
int up[N][M];
int mx[N][M];
 
vector<pii> g[N];
 
 
int find_set (int v) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set (parent[v]);
}
 
void union_sets (int a, int b) {
	a = find_set (a);
	b = find_set (b);
	if (a != b) {
		parent[b] = a;
	}
}
 
void dfs(int v) {
    used[v] = 1;
    for (auto [u, w] : g[v]) {
        if (used[u])
            continue;
        up[u][0] = v;
        mx[u][0] = w;
        lvl[u] = lvl[v] + 1;
        dfs(u);
    }
}
 
int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    iota(parent, parent + n, 0);
 
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        if (find_set(v) != find_set(u)) {
            g[v].emplace_back(u, i);
            g[u].emplace_back(v, i);
            union_sets(v, u);
        }
    }
 
    up[n][0] = n;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            int root = find_set(i);
            dfs(root);
            up[root][0] = n;
        }
    }
 
    for (int j = 1; j < M; ++j)
        for (int i = 0; i < n + 1; ++i) {
            up[i][j] = up[up[i][j - 1]][j - 1];
            mx[i][j] = max(mx[i][j - 1], mx[up[i][j - 1]][j - 1]);
        }
 
 
    while(q--) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        if (v == u) {
            cout << 0 << '\n';
            continue;
        }
        if(find_set(v) != find_set(u)) {
            cout << -1 << '\n';
            continue;
        }
        int res = 0;
        if (lvl[u] > lvl[v])
            swap(v, u);
        int k = lvl[v] - lvl[u];
        for (int i = 0; i < M; ++i) {
            if (k & (1 << i)) {
                res = max(res, mx[v][i]);
                v = up[v][i];
            }
        }
 
        if (v == u) {
            cout << res + 1 << '\n';
        }
        else {
            for (int i = M - 1; i >= 0; --i) {
                if (up[v][i] != up[u][i]) {
                    res = max({res, mx[v][i], mx[u][i]});
                    v = up[v][i];
                    u = up[u][i];
                }
            }
            cout << max({res, mx[v][0], mx[u][0]}) + 1 << '\n';
        }
    }
 
 
}
