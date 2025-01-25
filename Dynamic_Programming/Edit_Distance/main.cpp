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
const int N = 5005;
 
int dp[N][N];
 
int main() {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
 
    for (int i = 0; i < N; ++i)
        fill(dp[i], dp[i] + N, INF);
 
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j) {
            if (j == 0) {
                dp[i][j] = i;
            }
            else if (i == 0) {
                dp[i][j] = j;
            }
            else {
 
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
 
                if(s[i - 1] == t[j - 1]) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                }
            }
        }
 
    cout << dp[n][m] << '\n';
}
