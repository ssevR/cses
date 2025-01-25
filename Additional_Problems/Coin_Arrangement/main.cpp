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
int a[2][N];
 
int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            --a[i][j];
        }
    ll res = 0;
    int top = 0, bot = 0;
    for (int i = 0; i < n; ++i) {
        res += abs(top) + abs(bot);
        top += a[0][i];
        bot += a[1][i];
        if ((top < 0 && bot > 0) || (top > 0 && bot < 0)) {
            int x = min(abs(bot), abs(top));
            res += x;
 
            if (bot < 0)
                bot += x;
            else
                bot -= x;
 
            if (top < 0)
                top += x;
            else
                top -= x;
        }
    }
    cout << res << '\n';

    return 0;
}
