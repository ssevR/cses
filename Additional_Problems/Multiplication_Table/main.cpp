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
 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    int n;
    cin >> n;
    ll l = 0;
    ll r = 1ll * n * n + 1;
    while(r - l > 1) {
        ll mid = (r + l) / 2;
        ll cnt = 0;
        for (int i = 1; i <= n; ++i) {
            cnt += min(1ll * n, mid / i);
        }
        if (cnt <= 1ll * n * n / 2)
            l = mid;
        else 
            r = mid;
    }
    cout << r << '\n';

    return 0;
}
