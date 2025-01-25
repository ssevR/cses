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
    IOS;
    int n;
    cin >> n;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    vector<ll> pr(n);
    for (int i = 0; i < n; ++i) {
        pr[i] = a[i] - b[i];
        if (i)
            pr[i] += pr[i - 1];
    }
    sort(pr.begin(), pr.end());
    nth_element(pr.begin(), pr.begin() + n / 2, pr.end());
    ll mid = pr[n/2];
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        res += abs(pr[i] - mid);
    }
    cout << res << '\n';

    return 0;
}
