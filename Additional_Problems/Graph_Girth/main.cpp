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
    vector<vector<int> > g(n);
    vector<pii> edges(m);
    for (int i = 0; i < m; ++i){ 
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
        edges[i] = {v, u};
    }
    int res = INF;
    for (int i = 0; i < m; ++i) {
        int st = edges[i].fi;
        int en = edges[i].se;
        queue<int> q;
        vector<int> dist(n, INF);
        vector<int> used(n);
 
        q.push(st);
        dist[st] = 0;
        used[st] = 1;
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto u : g[v]) {
                if (used[u] == 1 || (u == st && v == en) || (u == en && v == st))
                    continue;
                used[u] = 1;
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
        if (dist[en] != INF)
            res = min(res, dist[en] + 1);
    }
    if (res == INF) res = -1;
    cout << res << '\n';

    return 0;
}
