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
    int n;
    cin >> n;
    vector<vector<int> > g(n);
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    vector<vector<int>> dp(n, vector<int>(2));
 
    auto dfs = [&](int v, int pr, auto&& dfs) -> void {
        for (auto u : g[v]) 
            if (u != pr) 
                dfs(u, v, dfs);
        int su = 0;
        for (auto u : g[v]) 
            if (u != pr)
                su += max(dp[u][0], dp[u][1]);
        dp[v][0] = su;
        for (auto u : g[v]) 
            if (u != pr)
                dp[v][1] = max(dp[v][1], su - max(dp[u][0], dp[u][1]) + dp[u][0] + 1);
 
    };
    dfs(0, -1, dfs);
    cout << max(dp[0][0], dp[0][1]) << '\n';

    return 0;
}
