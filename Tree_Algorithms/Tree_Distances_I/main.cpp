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
    vector<int> d1(n), d2(n);
 
    auto dfs = [&](int v, int pr, vector<int>& d, auto&& dfs) -> void {
        for (auto u : g[v]) 
            if (u != pr) {
                d[u] = d[v] + 1;
                dfs(u, v, d, dfs);
            }
    };
    d1[0] = 0;
    dfs(0, -1, d1, dfs);
    int v1 = max_element(d1.begin(), d1.end()) - d1.begin();
 
    d1[v1] = 0;
    dfs(v1, -1, d1, dfs);
    int v2 = max_element(d1.begin(), d1.end()) - d1.begin();
 
    d2[v2] = 0;
    dfs(v2, -1, d2, dfs);
 
    for (int i = 0; i < n; ++i) {
        cout << max(d1[i], d2[i]) << ' ';
    }
    cout << '\n';

    return 0;
}
