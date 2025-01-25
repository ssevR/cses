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
 
 
const int N = 4e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
ll dp[N];
vector<pii> g[N];
 
int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<pii, int> > projects(n);
    vector<int> f;
    for (int i = 0; i < n; ++i) {
        cin >> projects[i].fi.fi >> projects[i].fi.se >> projects[i].se;
        f.push_back(projects[i].fi.fi);
        f.push_back(projects[i].fi.se);
    }
    sort(f.begin(), f.end());
    f.erase(unique(f.begin(), f.end()), f.end());
 
    for (int i = 0; i < n; ++i) {
        projects[i].fi.fi = lower_bound(f.begin(), f.end(), projects[i].fi.fi) - f.begin() + 1;
        projects[i].fi.se = lower_bound(f.begin(), f.end(), projects[i].fi.se) - f.begin() + 1;
 
        g[projects[i].fi.se].push_back({projects[i].fi.fi, projects[i].se});
    }
    for (int i = 1; i < N; ++i) {
        dp[i] = dp[i - 1];
        for (auto [a, p] : g[i]) {
            dp[i] = max(dp[i],  p + dp[a - 1]);
        }
    }
 
    cout << dp[N - 1] << '\n';
}
