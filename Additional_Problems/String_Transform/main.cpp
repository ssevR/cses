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
    string t;
    cin >> t;
 
    vector<int> v(t.size());
    iota(v.begin(), v.end(), 0);
    stable_sort(v.begin(), v.end(), [&t](int a, int b) { return t[a] < t[b]; });
    string s;
    for (int i = v[0]; i;) s += t[i = v[i]];
    cout << s << '\n';

    return 0;
}
