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
vector<int> used;
vector<vector<int> > rev;
 
 
bool ford_bellman(int st, const vector<vector<pii> >& g, vector<ll>& dist) {
    fill(dist.begin(), dist.end(), LINF); // LINF == 1e18
    dist[st] = 0;
 
    int n = g.size();
    for (int i = 0; i < n; ++i) 
        for (int v = 0; v < n; ++v)
            for (auto [u, w] : g[v]) 
                if (dist[u] > dist[v] + w) {
                    dist[u] = dist[v] + w;  //watchout overflow if w is long long
                }
        for (int v = 0; v < n; ++v)
            for (auto [u, w] : g[v]) 
                if (dist[u] < LINF/2 && dist[u] > dist[v] + w && used[u]) {
                    return false;
                }
    return true;
 
}
 
void dfs(int v) {
    used[v] = 1;
    for (auto u : rev[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
}
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<pii> > g(n);
    rev.resize(n);
    used.resize(n);
    for (int i = 0; i < m; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].push_back({u, -w});
        rev[u].push_back(v);
    }
    dfs(n - 1);
 
    vector<ll> dist(n);
 
    if (!ford_bellman(0, g, dist)) {
        cout << "-1\n";
    }
    else {
        cout << -dist[n - 1] << '\n';
    }
}
