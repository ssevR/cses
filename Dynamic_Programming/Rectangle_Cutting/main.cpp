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
const int N = 505;
 
 
int dp[N][N];
 
int main() {
 
    dp[1][1] = 0;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            if (i == j) {
                dp[i][j] = 0;
                continue;
            }
 
            dp[i][j] = INF;
            for (int g = 1; g < i; ++g) {
                dp[i][j] = min(dp[i][j], 1 + dp[g][j] + dp[i - g][j]);
            }
            for (int h = 1; h < j; ++h) {
                dp[i][j] = min(dp[i][j], 1 + dp[i][h] + dp[i][j - h]);
            }
        }
    }
 
    int a, b;
    cin >> a >> b;
    cout << dp[a][b] << '\n';
}
