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
vector<ll> su;
vector<int> cnt;
vector<ll> res;
vector<vector<int> > g;
ll cur = 0;
int n;
 
void dfs1(int v, int pr = -1) {
 
    cnt[v] = 1;
    su[v] = 0;
 
    for (auto u : g[v] ){
        if (u != pr) {
            dfs1(u, v);
            cnt[v] += cnt[u];
            su[v] += su[u] + cnt[u];
        }
    }
}
 
void dfs2(int v, int pr, ll cur) {
    res[v] = cur;
    for (auto u : g[v])
        if (u != pr) {
            dfs2(u, v, cur - cnt[u] + (n - cnt[u]));
        }
}
 
int main() {
    cin >> n;
    g.resize(n);
    su.resize(n);
    cnt.resize(n);
    res.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
 
    dfs1(0);
    dfs2(0, -1, su[0]);
 
    for (int i = 0; i < n; ++i)
        cout << res[i] << ' ';
    cout << '\n';
 
}
