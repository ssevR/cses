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
 
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
 
 
int main() {
    IOS;
    int n;
    cin >> n;
 
    vector<int> used(n);
    vector<int> in(n);
 
    unordered_map<long long, pair<int, pii> , custom_hash> cycle;
    unordered_map<long long, pii , custom_hash> path;
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
 
    for (int v = 0; v < n; ++v) {
        if (path.count(v)) {
            cout << path[v].fi + cycle[path[v].se].se.se << ' ';
        }
        else {
            cout << cycle[v].se.se << ' ';
        }
    }
    cout << '\n';
 
}
