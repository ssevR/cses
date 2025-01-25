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
const int MOD = 1e9 + 7;
const int P = 1e9;
int su[N];
int deg2[N];
 
 
vector<int> find_centers(vector<vector<int> >& g) {
    int n = g.size();
    vector<int> dist(n);
    vector<int> pr(n);
    auto dfs = [&](int v, auto&& dfs)->void {
        for (auto u : g[v]) {
            if (u == pr[v]) continue;
            dist[u] = dist[v] + 1;
            pr[u] = v;
            dfs(u, dfs);
        }
    };
    dfs(0, dfs);
    int d1 = max_element(dist.begin(), dist.end()) - dist.begin();
    dist[d1] = 0;
    pr[d1] = -1;
    dfs(d1, dfs);
    int d2 = max_element(dist.begin(), dist.end()) - dist.begin();
    vector<int> res(1, d2);
    for (int i = 0; i < dist[d2] / 2; ++i) {
        res[0] = pr[res[0]];
    }
    if (dist[d2] % 2)
        res.push_back(pr[res[0]]);
    return res;
}
 
int find_hash(int v, vector<vector<int> > &g, int p = -1) {
    su[v] = 1;
 
    vector<pii> h;
    for (auto u : g[v]) {
        if (u == p)
            continue;
        auto cur_hash = find_hash(u, g, v);
        h.emplace_back(cur_hash, su[u]);
        su[v] += su[u];
    }
    sort(h.begin(), h.end());
    int res = 0;
    int cur = 0;
    for (int i = (int)h.size() - 1; i >= 0; --i) {
        res += 1ll * deg2[2 * cur] * h[i].fi;
        res %= MOD;
        cur += h[i].se;
    }
    return (deg2[su[v] * 2 - 1] + 1ll * res * P) % MOD;
}
 
int main() {
    IOS;
 
    deg2[0] = 1;
    for (int i = 1; i < N; ++i)
        deg2[i] = (1ll * deg2[i - 1] * P) % MOD;
 
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<vector<int> > g(n), h(n);
        for (int i = 0; i < n - 1; ++i) {
            int v, u;
            cin >> v >> u;
            --v, --u;
            g[v].push_back(u);
            g[u].push_back(v);
        }
        for (int i = 0; i < n - 1; ++i) {
            int v, u;
            cin >> v >> u;
            --v, --u;
            h[v].push_back(u);
            h[u].push_back(v);
        }
        auto cg = find_centers(g);
        auto ch = find_centers(h);
        if (cg.size() != ch.size()) {
            cout << "NO\n";
            continue;
        }
        int flag = 0;
        for (auto v : cg)
            for (auto u : ch) 
                if (find_hash(v, g) == find_hash(u, h) && !flag) {
                    cout << "YES\n";
                    flag = 1;
                }
        if (!flag)
            cout << "NO\n";
    }

    return 0;
}
