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
 
int n;
vector<ll> b, a;
multiset<ll> s;
 
int solve1(int z) {
    a[0] = (b[0] + b[1] - b[z]) / 2;
    a[1] = b[0] - a[0];
    a[2] = b[z] - a[1];
    if (min({a[0], a[1], a[2]}) > 0 && a[0] + a[1] == b[0] && a[0] + a[2] == b[1] && a[1] + a[2] == b[z]) {
        return 1;
    }
    else  {
        return 0;
    }
 
}
 
int solve2() {
    multiset<ll> f = s;
    for (int i = 1; i < n; ++i) {
        a[i] = *f.begin() - a[0];
        if (a[i] <= 0)
            return 0;
        for (int j = 0; j < i; ++j) {
            auto it = f.lower_bound(a[j] + a[i]);
            if (it == f.end())
                return 0;
            f.erase(it);
        }
    }
    return 1;
}
 
int main() {
    cin >> n;
    int sz = n * (n - 1) / 2;
    b.resize(sz);
    a.resize(n);
    for (int i = 0; i < sz; ++i) {
        cin >> b[i];
        s.insert(b[i]);
    }
    sort(b.begin(), b.end());
    for (int j = 2; j < sz; ++j) {
        if (solve1(j) && solve2()) {
            break;
        }
    }
    for (auto x : a)
        cout << x << ' ';
    cout << '\n';
}
