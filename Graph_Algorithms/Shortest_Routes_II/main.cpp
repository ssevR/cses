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
 
 
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
const int N = 500;
 
ll d[N][N];
 
int main() {
    int n, m, q;
    cin >> n >> m >> q;
 
    //d[i][j] len of edge between i and j, if doesnt exist then d[i][j] = INF
    for (int i = 0; i < n; ++i) {
        fill(d[i], d[i] + n, LINF);
        d[i][i] = 0;
    }
    while(m--) {
        int v, u, c;
        cin >> v >> u >> c;
        --v, --u;
        d[v][u] = d[u][v] = min(d[v][u], 1ll * c);
    }
 
 
 
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
            }
        }
    }
 
    while(q--) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        if (d[v][u] < LINF)
            cout << d[v][u] << '\n';
        else 
            cout << "-1\n";
    }
 
}
