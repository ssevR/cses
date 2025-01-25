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
const ll LINF = 2e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
ll pr[(1 << 20)];
 
int main() {
    ll n;
    int k;
    cin >> n >> k;
    vector<ll> p(k);
    for (int i = 0; i < k; ++i)
        cin >> p[i];
 
    ll res = n;
    pr[0] = 1;
 
    for (int mask = 1; mask < (1 << k); ++mask) {
        int cnt = __builtin_popcount(mask);
        int ind = __builtin_ctz(mask);
        if (pr[mask ^ (1 << ind)]  >= LINF / p[ind]) {
            pr[mask] = LINF;
            continue;
        }
        else {
            pr[mask] = pr[mask^(1<<ind)] * p[ind];
        }
        if (cnt&1) {
            res -= n/pr[mask];
        }
        else {
            res += n/pr[mask];
        }
    }
    cout << n - res << '\n';

    return 0;
}
