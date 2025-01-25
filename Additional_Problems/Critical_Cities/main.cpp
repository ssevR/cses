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
 
 
vector<vector<int>> dominator_tree(vector<vector<int>> g, int root) {
    int n = g.size();
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    swap(p[root], p[0]);
    swap(g[0], g[root]);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < g[i].size(); ++j) {
            g[i][j] = p[g[i][j]];
        }
    }
    vector<vector<int>> tree(n);
    vector<vector<int>> bucket(n);
    vector<int> sdom(n), dom(n), par(n), label(n), dsu(n);
    vector<vector<int>> gi(n);
    vector<int> arr(n, -1), rev(n);
    int tm = 0;
 
    function<int(int, int)> ask = [&](int u, int x) {
        if (u == dsu[u]) return x ? -1 : u;
        int v = ask(dsu[u], x + 1);
        if (v < 0) return u;
        if (sdom[label[dsu[u]]] < sdom[label[u]])
            label[u] = label[dsu[u]];
        dsu[u] = v;
        return x ? v : label[u];
    };
    auto un = [&](int u, int v) {
        dsu[v] = u;
    };
 
    function<void(int)> dfs = [&](int v) {
        arr[v] = tm;
        rev[tm] = v;
        label[tm] = sdom[tm] = dsu[tm] = tm;
        ++tm;
        for (int k : g[v]) {
            if (arr[k] == -1) {
                dfs(k);
                par[arr[k]] = arr[v];
            }
            gi[arr[k]].push_back(arr[v]);
        }
    };
    dfs(0);
    // assert(tm == n);  // connected
 
    for (int i = n - 1; i >= 0; --i) {
        for (int j : gi[i]) {
            sdom[i] = min(sdom[i], sdom[ask(j, 0)]);
        }
        if (i != 0) bucket[sdom[i]].push_back(i);
        for (int w : bucket[i]) {
            int v = ask(w, 0);
            if (sdom[v] == sdom[w]) dom[w] = sdom[w];
            else dom[w] = v;
        }
        if (i != 0) un(par[i], i);
    }
    for (int i = 1; i < n; ++i) {
        if (dom[i] != sdom[i])
            dom[i] = dom[dom[i]];
        tree[rev[dom[i]]].push_back(rev[i]);
        tree[rev[i]].push_back(rev[dom[i]]);
    }
 
    swap(tree[root], tree[0]);
    for (int i = 0; i < tree.size(); ++i) {
        for (int j = 0; j < tree[i].size(); ++j) {
            tree[i][j] = p[tree[i][j]];
        }
    }
 
    return tree;
}
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
    }
    auto tr = dominator_tree(g, 0);
    vector<int> pr(n);
    auto dfs = [&](int v,auto &&dfs) -> void {
        for (auto u : tr[v]) {
            if (u == pr[v]) continue;
            pr[u] = v;
            dfs(u, dfs);
 
        }
    };
    dfs(0, dfs);
 
    vector<int> res;
    int cur = n - 1;
    while(cur != 0) {
        res.push_back(cur);
        cur = pr[cur];
    }
    res.push_back(0);
    sort(res.begin(), res.end());
    cout << res.size() << '\n';
    for (auto x : res)
        cout << x + 1 << ' ';
    cout << '\n';
}
