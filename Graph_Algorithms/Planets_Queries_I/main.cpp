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
 
const int L = 31;
 
int t[L][N];
 
 
 
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
 
    for (int i = 0; i < n; ++i) {
        cin >> t[0][i];
        --t[0][i];
    }
    for (int z = 1; z < L; ++z)
        for (int i = 0; i < n; ++i)
            t[z][i] = t[z - 1][t[z - 1][i]];
 
    while(q--) {
        int v, k;
        cin >> v >> k;
        --v;
        for (int i = 0; i < L; ++i)
            if (k & (1 << i))
                v = t[i][v];
        cout << v + 1 << '\n';
    }
}
