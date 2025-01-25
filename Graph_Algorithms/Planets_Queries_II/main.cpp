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
const int L = 20;
 
int t[L][N];
 
 
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
 
    vector<int> used(n);
    vector<int> in(n);
 
    unordered_map<long long, pair<int, pii> > cycle;
    unordered_map<long long, pii > path;
    // path[i] = {dist, v}
    // cycle[i] = {ind, {v, len} }
 
 
    for (int i = 0; i < n; ++i) {
        cin >> t[0][i];
        --t[0][i];
 
        ++in[t[0][i]];
    }
    for (int j = 1; j < L; ++j)
        for (int i = 0; i < n; ++i)
            t[j][i] = t[j - 1][t[j - 1][i]];
 
    for (int i = 0; i < n; ++i) {
        if (in[i] == 0) {
            int sz_cur_path = 0;
            int v = i;
 
            while(!used[v]) {
                ++sz_cur_path;
                used[v] = 1;
                v = t[0][v];
            }
            // v is beginning of the cycle for i or path 
            if (path.count(v)) {
                int dist = sz_cur_path;
                for (int j = i; dist > 0; j = t[0][j]) {
                    path[j] = {path[v].fi + dist, path[v].se};
                    --dist;
                }
                continue;
            }
 
            int dist = 0;
 
            if (!cycle.count(v)) {
                int len = 0;
                int cur = v;
                do {
                    cur = t[0][cur];
                    ++len;
                } while(cur != v);
 
                int ind = 0;
                do {
                    cycle[cur] = mp(ind, mp(v, len));
                    cur = t[0][cur];
                    ++ind;
                } while(cur != v);
 
                dist = sz_cur_path - len;
            }
            else {
                dist = sz_cur_path;
            }
 
            for (int j = i; dist > 0; j = t[0][j]) {
                path[j] = mp(dist, v);
                --dist;
            }
 
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            int len = 0;
            int cur = i;
 
            do {
                used[cur] = 1;
                cur = t[0][cur];
                ++len;
            } while(cur != i);
 
            int ind = 0;
            do {
                cycle[cur] = {ind, mp(i, len)};
                cur = t[0][cur];
                ++ind;
            } while(cur != i);
        }
    }
 
    while(q--) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        if (path.count(v) && path.count(u)) {
            if (path[v].se != path[u].se || path[v].fi < path[u].fi) {
                cout << -1 << '\n';
                continue;
            }
            int k = path[v].fi - path[u].fi;
 
 
            for (int i = 0; i < L; ++i)
                if (k & (1 << i))
                    v = t[i][v];
 
            if (v != u)
                cout << -1 << '\n';
            else
                cout << k << '\n';
        }
        else {
            int res = 0;
            if (path.count(v)) {
                res += path[v].fi;
                v = path[v].se;
            }
 
            if (!cycle.count(u) || cycle[v].se.fi != cycle[u].se.fi) {
                res = -1;
            }
            else {
                res += (cycle[u].fi - cycle[v].fi + cycle[v].se.se) % cycle[v].se.se;
            }
            cout << res << '\n';
        }
    }
}
