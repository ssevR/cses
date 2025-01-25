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
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int cur;
        cin >> cur;
        ++c[cur];
    }
    for (int i = mxA; i; --i) {
        int cnt = 0;
        for (int j = i; j < mxA; j +=i) {
            cnt += c[j];
        }
        if (cnt > 1) {
            cout << i << '\n';
            return 0;
        }
    }

    return 0;
}
