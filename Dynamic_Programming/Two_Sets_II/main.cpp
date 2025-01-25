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
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
 
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
int main() {
    int n;
    cin >> n;
    int sz = n * (n + 1) / 2;
    if (sz % 2) {
        cout << 0 << '\n';
        return 0;
    }
 
    vector<int> dp(sz + 1);
 
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = sz; j >= i; --j) {
            dp[j] = (dp[j - i] + dp[j]) % MOD;
        }
    }
 
    cout << 1ll * dp[sz / 2] * ((MOD + 1) / 2) % MOD << '\n';
}
