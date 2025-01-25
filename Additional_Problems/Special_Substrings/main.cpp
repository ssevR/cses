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
 
 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
 
 
 
struct vi_hash {
    std::size_t operator()(const std::vector<uint32_t> & vec) const {
 
        static const uint32_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        std::size_t seed = vec.size() + FIXED_RANDOM;
        for(auto x : vec) {
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = (x >> 16) ^ x;
            seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
 
 
//gp_hash_table<int32_t, int32_t, hash_int> table; // unordered_map
//gp_hash_table<int32_t, null_type, hash_int> // unordered_set
 
int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    //gp_hash_table<vector<uint32_t>, int, vi_hash> L; // unordered_map
    unordered_map<vector<uint32_t>, int, vi_hash> L;
    vector<uint32_t> cnt(26);
    vector<uint32_t> is(26);
    for (int i = 0; i < n; ++i)
        is[s[i] - 'a'] = 1;
 
    ll res = 0;
    ++L[cnt];
 
    for (int i = 0; i < n; ++i) {
        ++cnt[s[i] - 'a'];
        uint32_t mi = INF;
        uint32_t mx = 0;
        for (int j = 0; j < 26; ++j) 
            if (is[j]) {
                mi = min(mi, cnt[j]);
                mx = max(mx, cnt[j]);
            }
 
        vector<uint32_t> ad(26);
        for (int j = 0; j < 26; ++j) {
            if (is[j]) {
                ad[j] = cnt[j] - mi;
            }
        }
        res += L[ad];
        ++L[ad];
    }
    cout << res << '\n';

    return 0;
}
