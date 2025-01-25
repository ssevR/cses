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
 
 
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const int N = 1000000 + 5;
 
int d[N];
int prime[N];
int u[N];
void sieve_calc() {
    std::iota(prime, prime + N, 0);
 
    for (int i = 2; i * i < N; ++i) {
        if (prime[i] == i) {
            for (int j = i * i; j < N; j += i) 
                if (prime[j] == j)
                    prime[j] = i;
        }
    }
    u[1] = 1;
    for (int i = 2; i < N; ++i) {
        int cnt = 0;
        int val = i;
        while(val % prime[i] == 0) {
            val /= prime[i];
            ++cnt;
        }
        if (cnt > 1)
            u[i] = 0;
        else
            u[i] = -u[val];
    }
    
}
 
int main() {
    IOS;
    sieve_calc();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        for (int j = 1; j * j <= x; ++j) {
            if (x % j == 0) {
                ++d[j];
                if (j * j != x)
                    ++d[x/j];
            }
        }
    }
    ll res = 0;
    for (int i = 1; i < N; ++i) {
        res += 1ll * u[i] * d[i] * (d[i] - 1) / 2;
    }
    cout << res << '\n';
}
