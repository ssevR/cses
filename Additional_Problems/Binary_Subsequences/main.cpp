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
 
 
int len(int a, int b) {
    if (a == b)
        return 0;
    if (a > b)
        return len(a - b, b) + 1;
    return len(a, b - a) + 1;
}
 
string trace(int a, int b) {
    if (a == b)
        return"";
    if (a > b)
        return trace(a - b, b) + "1";
    return trace(a, b - a) + "0";
 
}
 
int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "0\n";
        return 0;
    }
    int A = 0, B = 0;
    int mi = INF;
 
    for (int a = 1; a <= n + 1; ++a) {
        int b = n + 2 - a;
        if (__gcd(a, b) == 1 && len(a, b) < mi) {
            A = a;
            B = b;
            mi = len(a, b);
        }
    }
    string res = trace(A, B);
    cout << res << '\n';
}
