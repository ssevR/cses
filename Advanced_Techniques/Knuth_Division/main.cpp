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
 
 
const int N = 5e3 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
int a[N];
ll pr[N];
ll dp[N][N];
int opt[N][N];
 
ll w(int l, int r) {
    return pr[r] - pr[l];
}
 
int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pr[i + 1] = pr[i] + a[i];
        fill(dp[i], dp[i] + n + 1, LINF);
        dp[i][i + 1] = 0;
        opt[i][i + 1] = i;
    }
    for (int l = n - 1; l >= 0; --l)
        for (int r = l + 2; r <= n; ++r) {
            int from = opt[l][r - 1];
            int to = opt[l + 1][r];
            for (int i = from; i <= to; ++i) {
                if (dp[l][r] > w(l, r) + dp[l][i] + dp[i][r]) {
                    dp[l][r] = w(l, r) + dp[l][i] + dp[i][r];
                    opt[l][r] = i;
                }
            }
        }
    cout << dp[0][n] << '\n';

    return 0;
}
