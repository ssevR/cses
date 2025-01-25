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
    int n;
    cin >> n;
    if (n % 4 == 1 || n % 4 == 2) {
        cout << "NO\n";
    }
    else if (n % 4 == 0) {
        cout << "YES\n";
        cout << n / 2 << '\n';
        for (int i = 1; i <= n / 4; ++i) {
            cout << i << ' ' << n - i + 1 << ' ';
        }
        cout << '\n' << n / 2 << '\n';
        for (int i = n / 4 + 1; i <= n / 2; ++i) {
            cout << i << ' ' << n - i + 1 << ' ';
        }
        cout << '\n';
    }
    else {
        cout << "YES\n";
        n -= 3;
        cout << n / 2 + 2 << '\n';
 
        cout << 1 << ' ' << 2 << ' ';
 
        for (int i = 1; i <= n / 4; ++i) {
            cout << i + 3 << ' ' << n - i + 1 + 3 << ' ';
        }
        cout << '\n' << n / 2 + 1 << '\n' << 3 << ' ';
 
        for (int i = n / 4 + 1; i <= n / 2; ++i) {
            cout << i + 3 << ' ' << n - i + 1 + 3 << ' ';
        }
        cout << '\n';
    }
 
    return 0;
}
