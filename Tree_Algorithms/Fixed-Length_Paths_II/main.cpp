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
int n, k1, k2;
vector<vector<int> > g(n);
ll res = 0;
 
ll get_prefix(vector<ll>& a, int pr) {
    if (pr < 0)
        return 0;
    if (pr >= a.size())
        return a.back();
    return a.back() - a[a.size() - pr - 1];
}
 
vector<ll> dfs(int v, int p) {
    vector<ll> cur{1};
    for (auto u : g[v]) {
        if (u == p)
            continue;
        auto a = dfs(u, v);
        a.push_back(a.back());
 
        if (a.size() > cur.size())
            swap(a, cur);
 
        for (int i = 0; i < a.size(); ++i) {
            int depth = a.size() - i - 1;
            ll val = a[i];
            if (i != 0)
                val -= a[i - 1];
            res += val * (get_prefix(cur, k2 + 1 - depth) - get_prefix(cur, k1 - depth));
        }
 
        for (int i = 0; i < a.size(); ++i) {
            cur[(int)cur.size() - (int)a.size() + i] += a[i];
        }
    }
    return cur;
}
 
int main() {
    IOS;
    cin >> n >> k1 >> k2;
    g.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    auto x = dfs(0, -1);
    cout << res << '\n';

    return 0;
}
