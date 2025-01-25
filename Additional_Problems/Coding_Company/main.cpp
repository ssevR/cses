#pragma GCC optimize("O3")
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define IOS ios::sync_with_stdio(false); cin.tie(0)
#define ll long long
#define ld long double
#define rep(i,a,n) for (int i=(int)(a);i<(int)(n);i++)
#define per(i,a,n) for (int i=(int)(n-1);i>=(int)(a);i--)
#define mp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define fi first
#define se second
 
 
const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int N = 100+5;
const int K = 10005;
const ll INF = 1e18;
const ld PI = 4*atan((ld)1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
 
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
 
 
int dp[N][N][K];
 
 
int su(int a, int b) {
    return (a + b < MOD) ? (a + b) : (a + b - MOD);
}
 
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
 
    dp[0][1][0] = 1;
    dp[0][0][0] = 1;
 
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int z = 0; z <= k; ++z) {
                int v = dp[i][j][z];
                int val = z + j * (a[i + 1] - a[i]);
                if (val <= k) {
                    if (j) dp[i + 1][j - 1][val] = su(dp[i + 1][j - 1][val], 1ll * v * j % MOD);//closed
                    dp[i + 1][j][val] = su(dp[i + 1][j][val], 1ll * v * j % MOD); //add to interval
                    dp[i + 1][j + 1][val] = su(dp[i + 1][j + 1][val], v); //opened
                    dp[i + 1][j][val] = su(dp[i + 1][j][val], v); //opened and closed
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i <= k; ++i) {
        res = su(res, dp[n - 1][0][i]);
    }
    cout << res << '\n';

    return 0;
}
