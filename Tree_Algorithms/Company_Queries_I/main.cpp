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
 
vector<vector<int> > g;
 
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    g.resize(n);
    vector<vector<int> > up(n + 1, vector<int>(19));
 
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        up[i][0] = p;
    }
    up[0][0] = n;
    up[n][0] = n;
 
    for (int j = 1; j < 19; ++j)
        for (int i = 0; i < n + 1; ++i)
            up[i][j] = up[up[i][j - 1]][j - 1];
 
    while(q--) {
        int v, k;
        cin >> v >> k;
        --v;
        for (int j = 0; j < 19; ++j)
            if (k & (1 << j))
                v = up[v][j];
        if (v == n) {
            cout << -1 << '\n';
        }
        else {
            cout << v + 1 << '\n';
        }
    }

    return 0;
}
