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
 
 
const int N = 1e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int dp[N];
 
int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        for (int j = N - x[i] - 1; j >= 0; --j) {
            if (dp[j])
                dp[j + x[i]] = 1;
        }
    }
    int res = accumulate(dp, dp + N, 0);
    cout << res - 1 << '\n';
    for (int i = 1; i < N; ++i)
        if (dp[i])
            cout << i << ' ';
    cout << '\n';
}
