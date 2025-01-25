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
    vector<int> d(n);
 
    auto dfs = [&](int v, int pr, auto&& dfs) -> void {
        for (auto u : g[v]) 
            if (u != pr) {
                d[u] = d[v] + 1;
                dfs(u, v, dfs);
            }
    };
    d[0] = 0;
    dfs(0, -1, dfs);
    int v = max_element(d.begin(), d.end()) - d.begin();
 
    d[v] = 0;
    dfs(v, -1, dfs);
    cout << *max_element(d.begin(), d.end()) << '\n';

    return 0;
}
