#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
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
 
 
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
const int N = 1001;
int bit[N][N];
int a[N][N];
int n, q;
 
int sum(int x, int y) {
    if (x < 0 || y < 0)
        return 0;
    int res = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            res += bit[i][j];
    return res;
}
 
void add(int x, int y, int delta) {
    for (int i = x; i < n; i = i | (i + 1))
        for (int j = y; j < n; j = j | (j + 1))
            bit[i][j] += delta;
}
 
int main() {
    IOS;
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            char ch;
            cin >> ch;
            if (ch == '*') {
                add(i, j, 1);
                a[i][j] = 1;
            }
        }
    while(q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            if (a[x][y]) {
                add(x, y, -1);
                a[x][y] = 0;
            }
            else {
                add(x, y, 1);
                a[x][y] = 1;
            }
        }
        else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            --x1, --y1, --x2, --y2;
            cout << sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1) << '\n';
        }
    }
}
