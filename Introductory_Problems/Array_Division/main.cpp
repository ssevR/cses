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
const int MX = 2e5+5;
const ll INF = 1e18;
const ld PI = 4*atan((ld)1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
 
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
 
int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
 
    ll l = -1;
    ll r = 1e15;
 
    while(r - l > 1) {
        ll med = (r + l) / 2;
        int cur = 0;
        ll sum = 0;
        int ok = 1;
 
        for (int i = 0; i < n; ++i) {
            if (a[i] > med) {
                ok = 0;
                break;
            }
            if (sum + a[i] <= med) {
                sum += a[i];
            }
            else {
                ++cur;
                sum = a[i];
            }
        }
 
        ++cur;
 
        if (ok && cur <= k) {
            r = med;
        }
        else {
            l = med;
        }
    }
 
    cout << l + 1 << '\n';
}
