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
    int n, t;
    cin >> n >> t;
 
    vector<int> k(n);
    for (int i = 0; i < n; ++i) {
        cin >> k[i];
    }
    
    ll l = 0, r = LINF + 10;
    while(r - l > 1) {
        ll mid = (r + l) / 2;
 
        ll cnt = 0;
        for (int i = 0; i < n; ++i) {
            cnt += mid / k[i];
            if (cnt >= t)
                break;
        }
        if (cnt < t)
            l = mid;
        else {
            r = mid;
        }
    }
    cout << r << '\n';
}
