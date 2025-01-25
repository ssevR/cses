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
    int a, b, n;
    cin >> a >> b >> n;
    vector<pii> xy(n);
    for (int i = 0; i < n; ++i) {
        cin >> xy[i].fi >> xy[i].se;
    }
    sort(xy.begin(), xy.end(), [](pii a, pii b) {
        return a.fi + b.se > a.se + b.fi;
    });
 
    auto  dp = vector(2, vector<ll>(n + 1));;
    multiset<int> s;
    priority_queue<int, vector<int>, greater<int> > q;
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        q.push(xy[i].fi);
        sum += xy[i].fi;
        if (q.size() > a) {
            sum -= q.top();
            q.pop();
        }
        dp[0][i] = sum;
    }
 
    while(!q.empty())
        q.pop();
 
    sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        q.push(xy[i].se);
        sum += xy[i].se;
        if (q.size() > b) {
            sum -= q.top();
            q.pop();
        }
        dp[1][i] = sum;
    }
    ll res = dp[1][0];
    for (int i = 0; i < n; ++i) {
        res = max(res, dp[0][i] + dp[1][i + 1]);
    }
    cout << res << '\n';
 
}
