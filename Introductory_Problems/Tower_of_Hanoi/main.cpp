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
 
void solve(int n, int s, int d, int a) {
    if (n == 1) {
        cout << s << ' ' << d << '\n';
        return;
    }
    solve(n - 1, s, a, d);
 
    cout << s << ' ' << d << '\n';
 
    solve(n - 1, a, d, s);
}
 
int main() {
    int n;
    cin >> n;
    cout << (1 << n) - 1 << '\n';
    solve(n, 1, 3, 2);
}
