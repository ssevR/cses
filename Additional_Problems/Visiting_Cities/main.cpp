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
 
 
 
// https://neerc.ifmo.ru/wiki/index.php?title=%D0%98%D1%81%D0%BF%D0%BE%D0%BB%D1%8C%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5_%D0%BE%D0%B1%D1%85%D0%BE%D0%B4%D0%B0_%D0%B2_%D0%B3%D0%BB%D1%83%D0%B1%D0%B8%D0%BD%D1%83_%D0%B4%D0%BB%D1%8F_%D0%BF%D0%BE%D0%B8%D1%81%D0%BA%D0%B0_%D1%82%D0%BE%D1%87%D0%B5%D0%BA_%D1%81%D0%BE%D1%87%D0%BB%D0%B5%D0%BD%D0%B5%D0%BD%D0%B8%D1%8F
// for undirected graph 
// returns vector of size n
 
vector<int> cut_points(vector<vector<int> >& g) {
    int n = g.size();
    int timer = 0;
    vector<int> used(n);
    vector<int> tin(n);
    vector<int> low(n);
    vector<int> is_art(n);
 
    auto dfs = [&](int v, int p, auto&&dfs) -> void {
        used[v] = 1;
        low[v] = tin[v] = ++timer;
 
        int children = 0;
        for (auto u : g[v]) {
            if (u == p)
                continue;
            else if (used[u])
                low[v] = min(low[v], tin[u]);
            else {
                ++children;
                dfs(u, v, dfs);
                if (p != -1 && low[u] >= tin[v]) 
                    is_art[v] = 1;
                low[v] = min(low[v], low[u]);
            }
        }
        if (p == -1 && children > 1) {
            is_art[v] = 1;
        }
    };
 
    for (int i = 0; i < n; ++i)
        if (!used[i]) dfs(i, -1, dfs);
 
 
    return is_art;
}
 
vector<long long> dij(int st, vector<vector<pair<int, int> > >& g) {
    int n = g.size();
    vector<long long> dist(n, LINF); // LINF = 1e18
 
    priority_queue<pair<long long, int > , vector<pair<long long, int> >, greater<> > q;
 
    q.push({0, st});
    while(!q.empty()) {
        auto [d, v] = q.top();
        q.pop();
 
        if (dist[v] < LINF)
            continue;
        dist[v] = d;
 
        for (auto [u, w] : g[v])
            q.push({d + w, u});
    }
 
    return dist;
}
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<pair<pii, int> > ed;
    vector<vector< pii > > g(n), rg(n);
 
    for (int i = 0; i < m; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].push_back({u, w});
        rg[u].push_back({v, w});
        ed.push_back(mp(mp(v, u), w));
    }
    auto dist0 = dij(0, g);
    auto dist1 = dij(n - 1, rg);
 
    vector<vector<int> > fin_g(n);
    for (auto e : ed) {
        int v = e.fi.fi;
        int u = e.fi.se;
        int w = e.se;
        if (dist0[v] + w + dist1[u] == dist0[n - 1]) {
            fin_g[v].push_back(u);
            fin_g[u].push_back(v);
        }
    }
    auto res = cut_points(fin_g);
    res[0] = res[n - 1] = 1;
    cout << accumulate(res.begin(), res.end(), 0) << '\n';
 
    for (int i = 0; i < n; ++i)
        if (res[i])
            cout << i + 1 << ' ';
    cout << '\n';

    return 0;
}
