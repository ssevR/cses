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
 
 
bool find_cycle(const vector<vector<int> >& g, vector<int>& cycle) {
    cycle.clear();
    int n = (int)g.size();
 
    vector<int> pr(n), color(n);
 
    auto dfs = [&](int v, vector<int>& cycle, auto&& dfs) -> bool { 
        color[v] = 1;
        for (auto u : g[v]) {
            if (color[u] == 0) {
                pr[u] = v;
                if (dfs(u, cycle, dfs)) { return true; };
            }
            else if (color[u] == 1) {
                int cur = v;
                while(cur != u) {
                    cycle.push_back(cur);
                    cur = pr[cur];
                }
                cycle.push_back(u);
                cycle.push_back(v);
                reverse(cycle.begin(), cycle.end());
 
                return true;
            }
        }
        color[v] = 2;
 
        return false;
    };
 
    for (int i = 0; i < n; ++i) {
        if (!color[i]) {
            if (dfs(i, cycle, dfs)) { return true; };
        }
    }
 
    return false;
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
    }
 
    vector<int> cycle;
    if (find_cycle(g, cycle)) {
        cout << cycle.size() << '\n';
        for (auto v : cycle)
            cout << v + 1 << ' ';
        cout << '\n';
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
}
