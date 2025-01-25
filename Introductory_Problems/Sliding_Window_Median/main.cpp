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
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
 
    set<pii> s;
    s.insert({x[0], 0});
    auto mid = *s.begin();
 
    int sz = 1;
 
    if (k == 1) {
        cout << x[0] << ' ';
    }
 
    for (int i = 1; i < n; ++i) {
        auto cur = mp(x[i], i);
 
        s.insert(cur);
        ++sz;
 
        // 1 1 2 3 4 5 
        if (cur > mid && sz % 2) {
            mid = *(++s.lower_bound(mid));
        }
        else if (cur < mid && sz % 2 == 0) {
            mid = *(--s.lower_bound(mid));
        }
        //cout << mid.fi << '\n';
 
 
        if (i >= k) {
            auto last = mp(x[i - k], i - k);
            s.erase(last);
            --sz;
 
            if (last > mid && sz % 2 == 0) {
                mid = *(--s.lower_bound(mid));
            }
            else if (last < mid && sz % 2 == 1) {
                mid = *(++s.lower_bound(mid));
            }
            else if(last == mid) {
                if (sz % 2 == 1)
                    mid = *(s.lower_bound(mid));
                else {
                    mid = *(--s.lower_bound(mid));
                }
            }
        }
        //cout << mid.fi << '\n';
        //cout << '\n';
        if (i >= k - 1) {
            cout << mid.fi << ' ';
        }
    }
    cout << '\n';
}
