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
 
// https://usaco.guide/adv/BCC-2CC?lang=cpp
 
vector<vector<int>> biconnected_components(vector<vector<int>> &g,
                                           vector<bool> &is_cutpoint, vector<int> &id) {
	int n = (int)g.size();
 
	vector<vector<int>> comps;
	vector<int> stk;
	vector<int> num(n);
	vector<int> low(n);
 
	is_cutpoint.resize(n);
    id.resize(n);
 
	// Finds the biconnected components
	function<void(int, int, int &)> dfs = [&](int node, int parent, int &timer) {
		num[node] = low[node] = ++timer;
		stk.push_back(node);
		for (int son : g[node]) {
			if (son == parent) { continue; }
			if (num[son]) {
				low[node] = min(low[node], num[son]);
			} else {
				dfs(son, node, timer);
				low[node] = min(low[node], low[son]);
				if (low[son] >= num[node]) {
					is_cutpoint[node] = (num[node] > 1 || num[son] > 2);
					comps.push_back({node});
					while (comps.back().back() != son) {
						comps.back().push_back(stk.back());
						stk.pop_back();
					}
				}
			}
		}
	};
 
	int timer = 0;
	dfs(0, -1, timer);
	id.resize(n);
 
	// Build the block-cut tree
	function<vector<vector<int>>()> build_tree = [&]() {
		vector<vector<int>> t(1);
		int node_id = 0;
		for (int node = 0; node < n; node++) {
			if (is_cutpoint[node]) {
				id[node] = node_id++;
				t.push_back({});
			}
		}
 
		for (auto &comp : comps) {
			int node = node_id++;
			t.push_back({});
			for (int u : comp)
				if (!is_cutpoint[u]) {
					id[u] = node;
				} else {
					t[node].push_back(id[u]);
					t[id[u]].push_back(node);
				}
		}
		return t;
	};
 
	return build_tree();
}
 
 
int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int> > g(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    vector<int> id;
    vector<bool> is_cutpoint;
    auto tr = biconnected_components(g, is_cutpoint, id);
    int sz = tr.size();
 
    vector<int> lvl(sz);
    int M = ((int)log2(sz) + 1);
    vector<vector<int> > up(sz + 1, vector<int>(M));
    up[0][0] = sz;
    up[sz][0] = sz;
 
    auto dfs = [&](int v, auto&&dfs) ->void{
        for (auto u : tr[v]) {
            if (u == up[v][0]) continue;
 
            up[u][0] = v;
            lvl[u] = lvl[v] + 1;
            dfs(u, dfs);
        }
    };
    dfs(0, dfs);
 
 
    for (int j = 1; j < M; ++j)
        for (int i = 0; i < sz + 1; ++i)
            up[i][j] = up[up[i][j - 1]][j - 1];
 
    auto lca = [&](int v, int u)->int {
        if (lvl[u] > lvl[v])
            swap(v, u);
        int k = lvl[v] - lvl[u];
        for (int i = 0; i < 18; ++i) {
            if (k & (1 << i))
                v = up[v][i];
        }
        if (v == u) {
            return v;
        }
        for (int i = M - 1; i >= 0; --i) {
            if (up[v][i] != up[u][i]) {
                v = up[v][i];
                u = up[u][i];
            }
        }
        return up[v][0];
    };
    while(q--) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b, --c;
        if (a == c || b == c) {
            cout << "NO\n";
            continue;
        }
        else if (!is_cutpoint[c]) {
            cout << "YES\n";
            continue;
        }
        a = id[a];
        b = id[b];
        c = id[c];
        int l[3] = {lca(a, b), lca(a, c), lca(b, c)};
        if (l[0] == c || (l[1] == l[0] && l[2] == c) || (l[2] == l[0] && l[1] == c)) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
    }

    return 0;
}
