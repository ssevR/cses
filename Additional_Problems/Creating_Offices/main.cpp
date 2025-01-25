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
int n, d;
 
int up[N], up_v[N];
set<int> res[N];
vector<vector<int> > g;
 
void solve(int v, int p = -1) {
    vector<pii> ch_dis;
    int mx_u = -1, mx_sz = 0;
    for (auto u : g[v]) {
        if (u == p) continue;
        solve(u, v);
        ch_dis.emplace_back(up[u] - 1, u);
        if (int(res[u].size()) > mx_sz) {
            mx_sz = res[u].size();
            mx_u = u;
        }
    }
    if (mx_u != -1) {
        swap(res[mx_u], res[v]);
    }
    for (auto u : g[v]) {
        if (u == p || u == mx_u) continue;
        res[v].insert(res[u].begin(), res[u].end());
    }
    sort(ch_dis.begin(), ch_dis.end());
 
    while(ch_dis.size() >= 2 && ch_dis.back().fi + ch_dis[ch_dis.size() - 2].fi > d) {
        res[v].erase(up_v[ch_dis.back().se]);
        ch_dis.pop_back();
    }
    if (ch_dis.empty() || ch_dis.back().fi == 0) {
        up[v] = d;
        up_v[v] = v;
        res[v].insert(v);
    }
    else {
        up[v] = ch_dis.back().fi;
        up_v[v] = up_v[ch_dis.back().se];
    }
    
}
 
 
 
 
int main() {
    IOS;
    cin >> n >> d;
    g.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
 
    solve(0);
    cout << res[0].size() << '\n';
    for (auto x : res[0]) 
        cout << x + 1 << ' ';
    cout << '\n';

    return 0;
}
