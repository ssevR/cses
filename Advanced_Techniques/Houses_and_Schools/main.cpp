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
 
ll dp[N][N], pr[N];
ll w[N][N];
int c[N], opt[N][N];
 
int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        pr[i + 1] = c[i] + pr[i];
    }
    for (int i = 0; i < n; ++i) {
        int ind = i;
        ll suml = 0;
        ll sumr = 0;
        ll val = 0;
        w[i][i] = 0;
        for (int j = i - 1; j >= 0; --j) {
            suml += c[j];
            val += 1ll * c[j] * (ind - j);
            while(suml > sumr + c[ind]) {
                val += sumr + c[ind] - suml;
                sumr += c[ind];
                suml -= c[ind - 1];
                --ind;
            }
            w[j][i] = val;
        }
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
                if (dp[ki][ni] > dp[ki - 1][i] + w[i][ni - 1]) {
                    dp[ki][ni] = dp[ki - 1][i] + w[i][ni - 1];
                    opt[ki][ni] = i;
                }
            }
        }
    }
    cout << dp[k][n] << '\n';

    return 0;
}
