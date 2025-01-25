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
 
 
pair<bool, vector<int> >  find_negative_cycle(int st, const vector<vector<pii> >& g) {
    int n = g.size();
    vector<ll> dist(n, 0);
    dist[st] = 0;
    vector<int> pr(n);
 
    for (int i = 0; i < n; ++i) 
        for (int v = 0; v < n; ++v)
            for (auto [u, w] : g[v]) 
                if (dist[u] > dist[v] + w) {
                    dist[u] = dist[v] + w;  //watchout overflow if w is long long
                    pr[u] = v;
                }
        for (int v = 0; v < n; ++v)
            for (auto [u, w] : g[v]) 
                if (dist[u] > dist[v] + w) {
                    int cur = v;
                    for (int i = 0; i < n; ++i)
                        cur = pr[cur];
 
                    vector<int> res;
 
                    int beg = cur;
                    do {
                        res.push_back(cur);
                        cur = pr[cur];
                    }while(beg != cur);
 
                    res.push_back(beg);
 
                    reverse(res.begin(), res.end());
                    return {true, res};
                }
    return {false, vector<int>()};
}
 
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pii> > g(n);
    for (int i = 0; i < m; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].push_back({u, w});
    }
 
    auto [is_cycle, cycle] = find_negative_cycle(0, g);
    if (is_cycle) {
        cout << "YES\n";
        for (auto v : cycle) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }
    else {
        cout << "NO\n";
    }
}
