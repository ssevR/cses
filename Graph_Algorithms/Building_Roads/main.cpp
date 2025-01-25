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
vector<int> used;
 
void dfs(int v) {
    used[v] = 1;
    for (auto u : g[v])
        if (!used[u])
            dfs(u);
 
}
 
 
int main() {
    IOS;
    int n;
    cin >> n;
    g.resize(n);
    used.resize(n);
 
    int m;
    cin >> m;
    while(m--) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
 
    vector<pii> res;
 
    dfs(0);
    int last = 0;
    for (int i = 1; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
            res.push_back({last, i});
            last = i;
        }
    }
 
    cout << res.size() << '\n';
    for (auto x : res)
        cout << x.fi + 1 << ' ' << x.se + 1 << '\n';
    return 0;
}
 
