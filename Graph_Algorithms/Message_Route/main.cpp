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
 
 
pair<vector<int>, vector<int> >  bfs(int st, const vector<vector<int> > & g) {
    int n = g.size();
    vector<int> used(n);
 
    queue<int> q;
    q.push(st);
 
    vector<int> dist(n, INF); // INF == 1e9
    vector<int> parent(n);
 
    used[st] = 1;
    dist[st] = 0;
 
 
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : g[v]) {
            if (!used[u]) {
                used[u] = 1;
                q.push(u);
                dist[u] = dist[st] + 1;
                parent[u] = v;
            }
        }
    }
    
    return mp(dist, parent);
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
        g[u].push_back(v);
    }
    auto [dist, parent] = bfs(0, g);
 
    if (dist[n - 1] == INF) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
 
    vector<int> res;
 
    int cur = n - 1;
    while(cur != 0) {
        res.push_back(cur);
        cur = parent[cur];
    }
    res.push_back(0);
    reverse(res.begin(), res.end());
    cout << res.size() << '\n';
    for (auto v : res) {
        cout << v + 1 << ' ';
    }
    cout << '\n';
}
