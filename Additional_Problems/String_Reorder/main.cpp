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
 
 
int check(vector<int>& cnt, int fi) {
    auto it = max_element(cnt.begin(), cnt.end());
    int mx = *it;
    int ind = it - cnt.begin();
 
    int su = accumulate(cnt.begin(), cnt.end(), 0);
    if (su % 2 == 0) {
        if (mx * 2 <= su)
            return 1;
        else 
            return 0;
    }
    else {
        if (mx * 2 < su || (mx * 2 == su + 1 && fi != ind)) 
            return 1;
        else 
            return 0;
    }
}
 
int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> cnt(26);
 
    for (auto x : s)
        ++cnt[x - 'A'];
    if (!check(cnt, -1)) {
        cout << -1 << '\n';
        return 0;
    }
    int last = -1;
    string res;
    for (int i = 0; i < n; ++i) {
        for (int z = 0; z < 26; ++z) {
            if (cnt[z] > 0 && z != last) {
                --cnt[z];
                if (check(cnt, z)) {
                    res += char('A' + z);
                    last = z;
                    break;
                }
                else {
                    ++cnt[z];
                }
            }
        }
    }
    cout << res << '\n';
}
