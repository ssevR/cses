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
 
long double dp[101][601];
 
double round_p( double x, int p ){
    double d = std::pow(10,p+1);
    return ((x*d)+5)/d;
}
 
int main() {
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= (i - 1) * 6; ++j)
            for (int k = 1; k <= 6; ++k)
                dp[i][j + k] += dp[i - 1][j];
    }
 
    long double res = 0;
    for (int j = a; j <= b; ++j) {
        res += dp[n][j];
    }
    long double su = 0;
    for (int j = 0; j <= 6 * n; ++j)
        su += dp[n][j];
 
    cout << fixed << setprecision(6) << res/su << '\n';
}
