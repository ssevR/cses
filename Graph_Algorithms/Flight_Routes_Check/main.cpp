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
 
void dfs(int v, const vector<vector<int> >& g, vector<int>& dist) {
    for (auto u : g[v]) {
        if (dist[u] == INF) {
            dist[u] = dist[v] + 1;
            dfs(u, g, dist);
        }
    }
}
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(n), rev(n);
 
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        rev[u].push_back(v);
    }
 
    vector<int> dist[2];
    dist[0].assign(n, INF);
    dist[1].assign(n, INF);
 
    dist[0][0] = 0;
    dfs(0, g, dist[0]);
 
    dist[1][0] = 0;
    dfs(0, rev, dist[1]);
 
    for (int i = 0; i < n; ++i) {
        if (dist[0][i] == INF) {
            cout << "NO\n";
            cout << 1 << ' ' << i + 1 << '\n';
            return 0;
        }
        else if (dist[1][i] == INF) {
            cout << "NO\n";
            cout << i + 1 << ' ' << 1 << '\n';
            return 0;
        }
    }
 
    cout << "YES\n";
}
