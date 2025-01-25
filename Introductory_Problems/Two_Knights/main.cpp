// $%D%$.$%M%$.$%Y%$
// $%h%$:$%m%$:$%s%$
 
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
const int INF = 1e9;
const int N = 1e4 + 10;
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
ll dp[N];
 
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
int main() {
    IOS;
    dp[1] = 0;
    dp[2] = 6;
    dp[3] = 28;
    dp[4] = 96;
    dp[5] = 252;
    dp[6] = 550;
    dp[7] = 1056;
    for (int i = 8; i < N; ++i) {
        ll cnt[9];
        fill(cnt, cnt + 9, 0ll);
        cnt[2] = 4;
        cnt[3] = 8;
        cnt[4] = (i - 4) * 4 + 4;
        cnt[6] = (i - 4) * 4;
        cnt[8] = 1ll * i * i - cnt[2] - cnt[3] - cnt[4] - cnt[6];
 
        dp[i] = 1ll * i * i * (1ll * i * i - 1) / 2;
        for (int j = 0; j < 9; ++j) {
            dp[i] -= cnt[j] * j / 2;
        }
    }
 
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cout << dp[i] << '\n';
    }
    return 0;
}
