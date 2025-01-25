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
    ll x;
    cin >> n >> x;
 
    vector<ll> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
 
    map<ll, pii> mp;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (mp.count(x - a[i] - a[j])) {
                auto [f1, f2] = mp[x - a[i] - a[j]];
                cout << f1 + 1 << ' ' << f2 + 1 << ' ' << i + 1 << ' ' << j + 1 << '\n';
                return 0;
            }
        }
        for (int j = 0; j < i; ++j) {
            mp[a[j] + a[i]] = {j, i};
        }
    }
    cout << "IMPOSSIBLE\n";
}
