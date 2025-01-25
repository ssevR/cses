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
    vector <pii> v;
    vector<pii> res;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        sum += x;
        v.emplace_back(x, i);
    }
    sort(v.begin(), v.end());
    if (sum % 2 || v.back().fi * 2 > sum) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    while(!v.empty()) {
        int cnt = v.back().fi;
        int cur = v.back().se;
        v.pop_back();
        if (!cnt)
            continue;
        for (int i = (int)v.size() - 1; i >= 0 && cnt && v[i].fi > 0;) {
            int cur_cnt = upper_bound(v.begin(), v.begin() + i + 1, mp(v[i].fi, INF)) - lower_bound(v.begin(), v.begin() + i + 1, mp(v[i].fi, 0));
            for (int j = i - cur_cnt + 1; j <= i && cnt > 0; ++j) {
                v[j].fi -= 1;
                --cnt;
                res.emplace_back(cur, v[j].se);
            }
            i -= cur_cnt;
        }
        if (cnt > 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    cout << res.size() << '\n';
    for (auto x : res)
        cout << x.fi + 1 << ' ' << x.se + 1 << '\n';

    return 0;
}
