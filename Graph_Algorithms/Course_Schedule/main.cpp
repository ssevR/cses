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
 
 
// if the graph is not DAG, return empty vector
vector<int> top_sort(const vector<vector<int> >& g) {
    int n = (int)g.size();
    vector<int> used(n, 0), is_parent(n, 0), res;
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
 
    for (int v = 0; v < n; v++) {
        if (used[v] == 0) {
            if (dfs(v, dfs) == false) return vector<int>();
        }
    }
    reverse(res.begin(), res.end());
    return res;
}
 
int main() {
    int n;
    cin >> n;
    vector<vector<int> > g(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
    }
 
    vector<int> res = top_sort(g);
    if (res.empty()) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        for (auto v : res) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }
 
    return 0;
}
