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
 
vector<int> col;
vector<int> used;
vector<int> is_parent;
 
 
 
// if the graph is not DAG, return empty vector
vector<int> top_sort(const vector<vector<int> >& g, vector<int> perm) {
    vector<int> res;
    auto dfs = [&](int v, auto&& dfs) -> bool {
        if (is_parent[v] == 1) return false;
        if (!used[v]) {
            used[v] = 1;
            is_parent[v] = 1;
            for (auto u : g[v]) {
                if (!dfs(u, dfs)) return false;
            }
            res.push_back(v);
            is_parent[v] = 0;
        }
        return true;
    };
 
    for (auto v : perm) {
        if (used[v] == 0) {
            if (dfs(v, dfs) == false) return vector<int>();
        }
    }
    reverse(res.begin(), res.end());
    return res;
}
 
void dfs(int v, vector<vector<int> >& gg) {
    for (auto u : gg[v]) {
        if (!col[u]) {
            col[u] = col[v];
            dfs(u, gg);
        }
    }
}
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    col.resize(n);
    used.resize(n);
    is_parent.resize(n);
 
    vector<vector<int> > g(n), gg(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        gg[v].push_back(u);
        gg[u].push_back(v);
    }
    vector<int> is_cycle;
    int c = 0;
    for (int i = 0; i < n; ++i) {
        if (!col[i]) {
            ++c;
            col[i] = c;
            dfs(i, gg);
        }
    }
    vector<vector<int> > perm(c);
 
    for (int i = 0; i < n; ++i) {
        perm[col[i] - 1].push_back(i);
    }
 
    int res = 0;
    for (int i = 0; i < c; ++i) {
        if (top_sort(g, perm[i]).empty()) {
            res += perm[i].size();
        }
        else {
            res += perm[i].size() - 1;
        }
    }
    cout << res << '\n';

    return 0;
}
