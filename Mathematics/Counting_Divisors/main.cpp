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
 
 
const int N = 1e6 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int prime[N];
void sieve_calc() {
    std::iota(prime, prime + N, 0);
 
    for (int i = 2; i * i < N; ++i) {
        if (prime[i] == i) {
            for (int j = i * i; j < N; j += i) 
                if (prime[j] == j)
                    prime[j] = i;
        }
    }
}
 
int main() {
    IOS;
    sieve_calc();
 
    int t;
    cin >> t;
    while(t--) {
        int x;
        cin >> x;
        int res = 1;
 
        while(x > 1) {
            int cnt = 0;
            int cur = prime[x];
            while(x % cur == 0) {
                x /= cur;
                ++cnt;
            }
            res *= (cnt + 1);
        }
 
        cout << res << '\n';
    }

    return 0;
}
