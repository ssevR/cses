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
    int n, x;
    cin >> n >> x;
    auto a = vector(3, vector<int>(n));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];
    vector<int> dp(x + 1);
    for (int i = 0; i < n; ++i) {
        while(a[2][i] > 0) {
            int cur = (a[2][i] + 1) / 2;
            a[2][i] -= cur;
            for (int j = x; j >= 0 && j - a[0][i] * cur >= 0; --j) {
                dp[j] = max(dp[j], dp[j - a[0][i] * cur] + a[1][i] * cur);
            }
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << '\n';
}
