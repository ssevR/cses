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
 
 
vector<vector<long long> > dij(int st, vector<vector<pair<int, int> > >& g, int k) {
    int n = g.size();
    vector<vector<long long> > dist(n, vector<long long> (k, LINF)); // LINF = 1e18
    vector<int> sz(n);
 
    priority_queue<pair<long long, int > , vector<pair<long long, int> >, greater<> > q;
 
    q.push({0, st});
    while(!q.empty()) {
        auto [d, v] = q.top();
        q.pop();
 
        if (sz[v] == k)
            continue;
        dist[v][sz[v]] = d;
        ++sz[v];
 
        for (auto [u, w] : g[v])
            q.push({d + w, u});
    }
 
    return dist;
}
 
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pii> > g(n);
    for (int i = 0; i < m; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].push_back({u, w});
    }
 
    auto dist = dij(0, g, k);
    for (int i = 0; i < k; ++i)
        cout << dist[n - 1][i] << ' ';
    cout << '\n';
}
