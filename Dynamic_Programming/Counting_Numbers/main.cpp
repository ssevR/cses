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
const int ST = 18;
const int D = 10;
ll deg[ST];
 
ll solve(ll n) {
    if (n < 0) {
        return 0;
    }
    else if (n == 1000000000000000000ll) {
        --n;
    }
 
    ll dp[2][ST][D];
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < ST; ++j)
            fill(dp[i][j], dp[i][j] + D, 0ll);
 
    for (int d = 0; d < D; ++d) {
        dp[0][0][d] = 1;
        if (d <= n % 10)
            dp[1][0][d] = 1;
    }
 
    for (int j = 1; j < ST; ++j) {
        for (int d = 0; d < D; ++d) {
            for (int d1 = 0; d1 < D; ++d1) {
                if (d1 != d) {
                    dp[0][j][d] += dp[0][j - 1][d1];
 
                    if (d < (n / deg[j]) % 10) {
                        dp[1][j][d] += dp[0][j - 1][d1];
                    }
                    else if (d == (n / deg[j]) % 10) {
                        dp[1][j][d] += dp[1][j - 1][d1];
                    }
                }
            }
        }
    }
    ll res = 0;
    for (int j = 0; j < ST && deg[j] <= n; ++j) {
        for (int d = 1; d < D; ++d) {
            if (deg[j] * 10 > n && (n / deg[j]) % 10 == d) {
                res += dp[1][j][d];
            }
            else if(deg[j] * 10 <= n || d < (n/deg[j]) % 10) {
                res += dp[0][j][d];
            }
        }
    }
    res += 1;
 
    return res;
 
}
 
int main() {
    deg[0] = 1;
    for (int i = 1; i < ST; ++i)
        deg[i] = deg[i - 1] * 10;
    ll a, b;
    cin >> a >> b;
    cout << solve(b) - solve(a - 1) << '\n';
}
