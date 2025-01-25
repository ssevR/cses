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
 
 
 
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pr[i + 1] = pr[i] + a[i];
    }
    for (int r = 1; r <= n; ++r)
        for (int l = r - 1; l >= 0; --l) {
            dp[l][r] = max(pr[r] - pr[l + 1] - dp[l + 1][r] + a[l], 
                           pr[r - 1] - pr[l] - dp[l][r - 1] + a[r - 1]);
        }
 
    cout << dp[0][n] << '\n';
}
