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
 
 
const int N = 3e3 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
ll dp[N][N];
ll opt[N][N];
int a[N];
ll pr[N];
 
inline long long w(int l, int r) {
    return (pr[r] - pr[l]) * (pr[r] - pr[l]);
}
 
int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pr[i + 1] = pr[i] + a[i];
    }
    for (int ki = 0; ki <= k; ++ki) {
        fill(dp[ki], dp[ki] + n + 1, LINF);
        opt[ki][n + 1] = n;
    }
    dp[0][0] = 0;
 
    for (int ki = 1; ki <= k; ++ki) {
        for (int ni = n; ni >= 1; --ni) {
            int from = opt[ki - 1][ni];
            int to = opt[ki][ni + 1];
            for (int i = from; i <= to; ++i) {
                if (dp[ki][ni] > dp[ki - 1][i] + w(i, ni)) {
                    dp[ki][ni] = dp[ki - 1][i] + w(i, ni);
                    opt[ki][ni] = i;
                }
            }
        }
    }
    cout << dp[k][n] << '\n';

    return 0;
}
