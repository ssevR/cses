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
    ll k;
    cin >> n >> k;
    int i = 1;
    ll cur = 0;
    while(cur + i <= k) {
        cur += i;
        ++i;
    }
    int f = k - cur;
 
    for (int j = i; j >= 1; --j) {
        cout << j << ' ';
        if (j - 1 == f && i + 1 <= n) {
            cout << i + 1 << ' ';
        }
    }
    for (int j = i + 2; j <= n; ++j)
        cout << j << ' ';
    cout << '\n';

    return 0;
}
