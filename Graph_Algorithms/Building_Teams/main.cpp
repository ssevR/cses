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
 
vector<vector<int> > g;
vector<int> lvl;
vector<int> used;
 
 
 
void dfs(int v) {
    used[v] = 1;
    for (auto u : g[v]) {
        if (!used[u]) {
            used[u] = 1;
            lvl[u] = lvl[v] + 1;
            dfs(u);
        }
        else if ((lvl[v] + lvl[u]) % 2 == 0) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
}
 
int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    lvl.resize(n);
    used.resize(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs(i);
    for (int i = 0; i < n; ++i) {
        cout << lvl[i] % 2 + 1 << ' ';
    }
    cout << '\n';

    return 0;
}
