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
const ld PI = 4*atan((ld)1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
const int N = 1003;
 
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
char a[N][N];
int dp[N][N];
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<int> > cnt(n, vector<int>(m + 2));
    int x;
    cin >> x;
    if (x) {
        cnt[0][x] = 1;
    }
    else {
        for (int j = 1; j <= m; ++j) {
            cnt[0][j] = 1;
        }
    }
 
    for (int i = 1; i < n; ++i) {
        int x;
        cin >> x;
        if (x) {
            cnt[i][x] = (1ll * cnt[i - 1][x - 1] + cnt[i - 1][x] + cnt[i - 1][x + 1]) % MOD;
        }
        else {
            for (int j = 1; j <= m; ++j) {
                cnt[i][j] = (1ll * cnt[i - 1][j - 1] + cnt[i - 1][j] + cnt[i - 1][j + 1]) % MOD;
            }
        }
    }
 
    int ans = 0;
    for (int j = 1; j <= m; ++j) {
        ans = (ans + cnt[n - 1][j]) % MOD;
    }
    cout << ans << '\n';
}
