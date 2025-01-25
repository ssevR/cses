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
    auto a = vector(2, vector<int>(n));
    auto wa = vector(2, vector<int>(n));
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            --a[i][j];
            wa[i][a[i][j]] = j;
        }
    vector<vector<int> > g(n, vector<int>(2, -1));
    auto dfs = [&](int l, int r, int l2, int r2, auto&& dfs) -> int {
        int root = a[0][l];
        if (l + 1 == r)
            return root;
        int tmp = wa[1][a[0][l]] + 1;
        int mid = l + (tmp - l2);
 
        if (l + 1 < mid)
            g[root][0] = dfs(l + 1, mid, l2, l2 + mid - (l + 1), dfs);
        if (mid < r)
            g[root][1] = dfs(mid, r, r2 - (r - mid), r2, dfs);
        return root;
    };
    dfs(0, n, 0, n, dfs);
 
    auto dfs1 = [&](int v, auto&& dfs1) -> void {
        for (auto u : g[v])
            if (u != -1)
                dfs1(u, dfs1);
        cout << v + 1 << ' ';
    };
    dfs1(a[0][0], dfs1);
    cout << '\n';

    return 0;
}
