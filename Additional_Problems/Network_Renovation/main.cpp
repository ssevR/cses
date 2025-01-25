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
 
 
int find_leaftroid(vector<vector<int> >& g, int cnt) {
    int n = g.size();
    if (n == 1)
        return 0;
 
    vector<int> sz(n);
    auto dfs = [&](int v, int p, auto&& dfs) -> int {
        if (g[v].size() == 1)
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
        if (g[v].size() >= 2 && 2 * mx <= cnt && (cnt - sz[v]) * 2 <= cnt) {
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
    int cnt_leaf = 0;
    for (int i = 0; i < n; ++i) {
        if (g[i].size() == 1)
            ++cnt_leaf;
    }
    auto c = find_leaftroid(g, cnt_leaf);
    vector<vector<int> > leafs(g[c].size());
    auto dfs = [&](int v, int p, int id, auto&& dfs) -> void {
        if (g[v].size() == 1)
            leafs[id].push_back(v);
        for (auto u : g[v])
            if (u != p)
                dfs(u, v, id, dfs);
    };
    priority_queue<pii> q;
    for (int i = 0; i < g[c].size(); ++i) {
        dfs(g[c][i], c, i, dfs);
        q.push(mp(leafs[i].size(), i));
    }
    vector<pii> res;
    while(!q.empty()) {
        auto f1 = q.top();
        q.pop();
        if (q.empty()) {
            res.emplace_back(leafs[f1.se].back(), c);
            break;
        }
        auto f2 = q.top();
        q.pop();
        res.emplace_back(leafs[f1.se].back(), leafs[f2.se].back());
        leafs[f1.se].pop_back();
        leafs[f2.se].pop_back();
        --f1.fi;
        --f2.fi;
        if (f1.fi) {
            q.push(f1);
        }
        if (f2.fi) {
            q.push(f2);
        }
    }
    cout << res.size() << '\n';
    for (auto x : res)
        cout << x.fi + 1 << ' ' << x.se + 1 << '\n';
 
    return 0;
}
