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
    vector<vector<int> > dp(10);
 
    for (int k = 1; k <= 10; ++k) {
        for (int i = 0; i < k; ++i) {
            for (int j = (i + 1) * k; j > i * k; --j)
                dp[k - 1].push_back(j);
        }
    }
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        if (k * k < n) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        vector<int> res;
        while(k && (k - 1) * (k - 1) >= n - 1) {
            res.push_back(n);
            --k;
            --n;
        }
        if (k != 0) {
            for (auto x : dp[k - 1]) {
                if (x <= n)
                    res.push_back(x);
            }
        }
        for (auto x : res)
            cout << x << ' ';
        cout << '\n';
    }

    return 0;
}
