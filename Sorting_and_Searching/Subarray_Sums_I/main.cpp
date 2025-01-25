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
    IOS;
    int n;
    ll x;
    cin >> n >> x;
    map<ll, int> mp;
    ll pr = 0;
    vector<int> a(n);
    ll res = 0;
    ++mp[0];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pr += a[i];
        res += mp[pr - x];
 
        ++mp[pr];
    }
    cout << res << '\n';
}
