#pragma GCC optimize("O3")
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define IOS ios::sync_with_stdio(false); cin.tie(0)
#define ll long long
#define ld long double
#define rep(i,a,n) for (int i=(int)(a);i<(int)(n);i++)
#define per(i,a,n) for (int i=(int)(n-1);i>=(int)(a);i--)
#define mp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define fi first
#define se second
 
 
const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int INF = 1e9;
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
 
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
int cnt = 0;
const int N = 7;
 
int used[N][N];
int l = 1;
string s;
 
void solve(int x, int y) {
    if (x == N - 1 && y == 0 && l == N * N) {
        ++cnt;
    }
    if ((x == N - 1 && y == 0) ||
        ((x == 0 || x == N - 1)&& y > 0 && y < N - 1 && !used[x][y - 1] && !used[x][y + 1]) ||
        ((y == 0 || y == N - 1)&& x > 0 && x < N - 1 && !used[x - 1][y] && !used[x - 1][y]) ||
        (y > 0 && y < N - 1 && x > 0 && x < N - 1 && (
            (used[x][y + 1] && used[x][y - 1] && !used[x - 1][y] && !used[x + 1][y]) ||
            (!used[x][y + 1] && !used[x][y - 1] && used[x - 1][y] && used[x + 1][y])
            )) ||
        (N - 1 - x + + y > N * N - l)
        ) {
        return;
    }
    used[x][y] = 1;
 
    if (x && !used[x - 1][y] && (s[l - 1] == '?' || s[l - 1] == 'U')) {
        ++l;
        solve(x - 1, y);
        --l;
    }
    if (y && !used[x][y - 1] && (s[l - 1] == '?' || s[l - 1] == 'L')) {
        ++l;
        solve(x, y - 1);
        --l;
    }
    if (x < N - 1 && !used[x + 1][y] && (s[l - 1] == '?' || s[l - 1] == 'D')) {
        ++l;
        solve(x + 1, y);
        --l;
    }
 
    if (y < N - 1 && !used[x][y + 1] && (s[l - 1] == '?' || s[l - 1] == 'R')) {
        ++l;
        solve(x, y + 1);
        --l;
    }
 
    used[x][y] = 0;
    return;
}
 
int main() {
    IOS;
    cin >> s;
    solve(0, 0);
    cout << cnt << '\n';
}
