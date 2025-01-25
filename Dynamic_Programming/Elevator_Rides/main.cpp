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
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
    vector<pii> dp(1 << n);
 
    dp[0] = {1, 0};
    for (int mask = 1; mask < (1 << n); ++mask) {
        dp[mask] = {n + 1, 0};
 
        for (int j = 0; j < n; ++j){ 
            if (mask & (1 << j)) {
                auto cur = dp[mask ^ (1 << j)];
                if (cur.se + w[j] <= x) {
                    dp[mask] = min(dp[mask], mp(cur.fi, cur.se + w[j]));
                }
                else {
                    dp[mask] = min(dp[mask], mp(cur.fi + 1, w[j]));
                }
            }
        }
    }
 
    cout << dp[(1 << n) - 1].fi << '\n';
}
