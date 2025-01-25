#pragma GCC optimize("O3")
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define IOS ios::sync_with_stdio(false); cin.tie(0)
#define ll long long
#define ld long double
#define rep(i,a,n) for (int i=(int)(a);i<(int)(n);i++)
#define per(i,a,n) for (int i=(int)(n-1);i>=(int)(a);i--)
#define mp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define fi first
#define se second
 
 
const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int INF = 1e9;
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
 
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
bool cmp(pii a, pii b) {
    if (a.second != b.second) {
        return a.second < b.second;
    }
    else {
        return a.first <  b.first;
    }
}
 
int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    vector<pii> dat;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        dat.push_back({a, b});
    }
    sort(dat.begin(), dat.end(), cmp);
 
    int cnt = 0;
    multiset<int> s;
    for (int i = 0; i < k; ++i)
        s.insert(-1);
    for (int i = 0; i < dat.size(); ++i) {
        auto it = s.upper_bound(dat[i].first);
        if (it != s.begin()) {
            --it;
            s.erase(it);
            ++cnt;
            s.insert(dat[i].second);
        }
        /*if (dat[i].first >= cur) {
            ++cnt;
            cur = dat[i].second;
        }*/
    }
    cout << cnt << '\n';
}
