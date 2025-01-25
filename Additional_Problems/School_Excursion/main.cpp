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
 
 
const int N = 1e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
 
int main() {
    IOS;
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
    vector<int> used(n);
    auto dfs = [&](int v, auto&& dfs) -> int {
        used[v] = 1;
        int res = 1;
        for (auto u : g[v])
            if (!used[u]) {
                used[u] = 1;
                res += dfs(u, dfs);
 
            }
        return res;
    };
    vector<int> w;
    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            ++mp[dfs(i, dfs)];
    }
    for (auto [cur, cnt] : mp) {
        for (int st = 0; cnt > 0; ++st) {
            w.push_back(cur * min(1 << st, cnt));
            cnt -= (1<<st);
        }
    }
    bitset<N> dp;
    dp[0] = 1;
    for (auto cur : w) {
        dp |= (dp << cur);
    }
    for (int i = 1; i <= n; ++i)
        cout << dp[i];
    cout << '\n';
}
