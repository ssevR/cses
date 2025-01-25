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
const int INF = 1e9 + 10;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
 
 
 
using namespace std;
 
// return indexes
int main() {
    int n;
    cin >> n;
    vector<int> w(n), a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        w[a[i]] = i;
    }
    int res = 1;
    for (int i = 1; i < n; ++i) {
        if (w[i] < w[i - 1])
            ++res;
    }
    cout << res << '\n';
}
