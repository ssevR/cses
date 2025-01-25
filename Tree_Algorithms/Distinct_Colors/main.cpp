#pragma GCC optimize("O3,unroll-loops")
 
#include<algorithm>
#include<bitset>
#include<iostream>
#include<set>
 
#include <vector>
 
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
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
vector<set<int> > b;
vector<int> c, res;
vector<vector<int> > g;
 
void dfs (int v, int p) {
    int mx = 0;
    int mx_u = 0;
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs(u, v);
        if (b[u].size() > mx) {
            mx = b[u].size();
            mx_u = u;
        }
    }
 
    if (mx) {
        swap(b[v], b[mx_u]);
        for (auto u : g[v]) {
            if (u != p && u != mx_u) {
                b[v].insert(b[u].begin(), b[u].end());
                b[u].clear();
            }
        }
    }
    b[v].insert(c[v]);
    res[v] = b[v].size();
    return;
};
 
int main() {
    IOS;
    int n;
    cin >> n;
    c.resize(n);
    g.resize(n);
    b.resize(n);
    res.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> c[i];
 
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
 
    dfs(0, -1);
    for (int i = 0; i < n; ++i)
        cout << res[i] << ' ';
    cout << '\n';

    return 0;
}
