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
const int INF = 2e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<int> x(n + 1);
    x[n] = INF;
    vector<ll> pr(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        pr[i + 1] = pr[i] + x[i];
    }
    vector<vector<pair<int, int> > > v(n);
    vector<ll> res(q);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        v[a].push_back({b, i});
    }
    set<int> s;
    s.insert(n);
    vector<ll> f(n + 1);
 
    for (int i = n - 1; i >= 0; --i) {
        while(x[*s.begin()] <= x[i]) {
            s.erase(s.begin());
        }
        int nxt = *s.begin();
        f[i] = 1ll * (nxt - i) * x[i] - (pr[nxt] - pr[i]) + f[nxt];
 
        s.insert(i);
 
        for (auto [r, ind] : v[i]) {
            auto closest_ind = *(--s.upper_bound(r));
            res[ind] = f[i] - f[closest_ind] + 1ll * (r - closest_ind + 1) * x[closest_ind] - (pr[r + 1] - pr[closest_ind]);
        }
    }
    for (auto x : res)
        cout << x << '\n';
}
