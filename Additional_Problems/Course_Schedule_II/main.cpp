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
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(n);
    vector<int> deg(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[u].push_back(v);
        ++deg[v];
    }
    priority_queue<int> q;
    for (int i = 0; i < n; ++i)
        if (!deg[i])
            q.push(i);
    vector<int> res;
    while(!q.empty()) {
        int v = q.top();
        q.pop();
        res.push_back(v);
        for (auto u : g[v]) {
            --deg[u];
            if (deg[u] == 0)
                q.push(u);
        }
    }
    reverse(res.begin(), res.end());
    for (auto x : res)
        cout << x + 1 << ' ';
    cout << '\n';

    return 0;
}
