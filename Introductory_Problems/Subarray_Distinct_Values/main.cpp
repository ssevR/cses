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
const int MX = 2e5+5;
const ll INF = 1e18;
const ld PI = 4*atan((ld)1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
 
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
 
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
 
 
    unordered_map<long long, int, custom_hash> mp;
    int cnt = 0;
    int i = 0, j = 0;
    while(j < n && (cnt < k || (cnt == k && mp[x[j]] > 0))) {
        if (mp[x[j]] == 0) {
            ++cnt;
        }
 
        ++mp[x[j]];
        ++j;
    }
 
    long long res = 0;
 
    res += j - i;;
 
    while(i != n - 1) {
        if (mp[x[i]] == 1) {
            --cnt;
        }
        --mp[x[i]];
        ++i;
        while(j < n && (cnt < k || (cnt == k && mp[x[j]] > 0))) {
            if (mp[x[j]] == 0) {
                ++cnt;
            }
            ++mp[x[j]];
            ++j;
        }
 
        res += j - i;
    }
 
    cout << res << '\n';
}
