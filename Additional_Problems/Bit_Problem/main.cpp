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
 
 
const int N = 21;
const int M = (1 << N) - 1;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int F[2][1 << N];
 
int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        ++F[0][x[i]];
        ++F[1][x[i]];
    }
    for (int i = 0; i < N; ++i)
        for (int mask = 0; mask < (1 << N); ++mask) {
            if (mask & (1 << i))
                F[0][mask] += F[0][mask ^ (1 << i)];
            else
                F[1][mask] += F[1][mask ^ (1 << i)];
        }
    for (int i = 0; i < n; ++i)
        cout << F[0][x[i]] << ' ' << F[1][x[i]] << ' ' << n - F[0][M ^ x[i]] << '\n';
}
