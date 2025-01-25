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
    ll n;
    cin >> n;
    if (n == 1) {
        cout << 9 << '\n';
        return 0;
    }
    vector<ll> deg10(19);
    deg10[0] = 1;
    for (int i = 1; i < 19; ++i)
        deg10[i] = deg10[i - 1] * 10;
    ll l = 0, r = LINF;
    while(r - l > 1) {
        ll mid = (r + l) / 2;
        auto dp = vector(19, vector<ll> (10));
        auto val = vector<ll>(19);
        for (int j = 0; j < 9; ++j)
            dp[0][j] = 1;
        if (mid % 10 > 0)
            val[0] = 1;
 
        for (int i = 1; i < 19; ++i) {
            dp[i][0] = 2 * dp[i - 1][8] + deg10[i];
            for (int j = 1; j < 9; ++j)
                dp[i][j] = dp[i][j - 1] + dp[i - 1][8];
            int digit = mid / deg10[i] % 10;
            if (digit == 0) {
                val[i] = val[i - 1];
            }
            else if(digit == 1) {
                val[i] = val[i - 1] + dp[i - 1][8] + mid % deg10[i] + 1;
            }
            else {
                val[i] = val[i - 1] + dp[i][digit - 2];
            }
 
        }
        if (val[18] <= n) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    cout << l << '\n';

    return 0;
}
