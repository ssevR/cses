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
 
 
//gp_hash_table<int32_t, int32_t, hash_int> table; // unordered_map
 
 
struct hash_int {
    static uint32_t splitmix32(uint32_t x) {
        x += 0x9e3779b9;
        x = (x ^ (x >> 16)) * 0x21f0aaad;
        x = (x ^ (x >> 15)) * 0x735a2d97;
        x ^= x >> 15;
        return x;
    }
 
 
    uint32_t operator()(uint32_t x) const {
        static const uint32_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix32(x + FIXED_RANDOM);
    }
};
 
 
int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(n);
    gp_hash_table<int32_t, null_type, hash_int> s[31]; // unordered_set
    for (int i = 0; i < 31; ++i)
        s[i].insert(0);
 
    int su = 0;
    int res = 0;
 
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        su ^= a[i];
 
        int cur = 0;
        int suf = 0;
        for (int j = 30; j >= 0; --j) {
            if (su & (1 << j))
                suf |= (1 << j);
 
            s[j].insert(suf);
 
            int bit = ((su & (1 << j)) > 0);
            if (bit == 0) {
                if (s[j].find(cur | (1 << j)) != s[j].end())
                    cur |= (1 << j);
            }
            else {
                if (s[j].find(cur) != s[j].end());
                else
                    cur |= (1 << j);
            }
        }
        res = max(res, cur ^ su);
    }
    cout << res << '\n';
}
