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
    int n, m;
    cin >> n >> m;
    vector<vector<pii> > g(n);
    vector<pii> edges(m);
 
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        edges[i] = {v, u};
        g[v].emplace_back(u, i);
        g[u].emplace_back(v, i);
    }
    vector<int> color(n);
 
    auto dfs = [&](int v, auto&& dfs) -> int {
        color[v] = 1;
        vector<int> edge_indx;
        for (auto [u, ind] : g[v]) {
            if (color[u] == 0) {
                auto res = dfs(u, dfs);
                if (res > -1) {
                    if (edges[res].fi != u)
                        swap(edges[res].fi, edges[res].se);
                    if (edges[ind].fi != u)
                        swap(edges[ind].fi, edges[ind].se);
                }
                else {
                    edge_indx.push_back(ind);
                }
            }
            else if (color[u] == 2) {
                edge_indx.push_back(ind);
            }
        }
        color[v] = 2;
        for (auto ind : edge_indx) {
            if (edges[ind].fi != v)
                swap(edges[ind].fi, edges[ind].se);
        }
        if (edge_indx.size() % 2) {
            return edge_indx.front();
        }
        else {
            return -1;
        }
    };
    for (int i = 0; i < n; ++i) {
        if (!color[i] && dfs(i, dfs) != -1) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    for (auto [v, u] : edges)
        cout << v + 1 << ' ' << u + 1 << '\n';

    return 0;
}
