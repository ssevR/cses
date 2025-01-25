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
const int mxA = 1e6 + 5;
int c[mxA];
 
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
int main() {
    int t;
    cin >> t;
    while(t--) {
        int x, y;
        cin >> y >> x;
        int sz = max(x, y);
        ll ans;
        if (sz % 2) {
            if (y == sz) {
                ans = 1ll * (sz - 1) * (sz - 1) + x;
            }
            else {
                ans = 1ll * sz * sz - y + 1;
            }
        }
        else {
            if (y == sz) {
                ans = 1ll * sz * sz - x + 1;
            }
            else {
                ans = 1ll * (sz - 1) * (sz - 1) + y;
            }
        }
        cout << ans << '\n';
    }
}
