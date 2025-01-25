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
const int LOGN = 20;
 
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    IOS;
    int n;
    ll k;
    cin >> n >> k;
    ll su = 0;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        su += x[i];
    }
    if (su <= k) {
        cout << 1 << '\n';
        return 0;
    }
 
 
    vector<vector<int> > next(n, vector<int>(LOGN));
    vector<vector<ll> > f(n, vector<ll>(LOGN));
 
    ll cur = 0;
    int j = n - 1;
    for (int i = 0; i < n; ++i) {
        while(cur + x[(j + 1) % n] <= k) {
            j = (j + 1) % n;
            cur += x[j];
        }
        next[i][0] = (j + 1) % n;
        f[i][0] = cur;
        cur -= x[i];
    }
 
    int res = 0;
    j = 0;
    while(true) {
        ++res;
        if (next[j][0] < j) {
            break;
        }
        j = next[j][0];
    }
    for (int j = 1; j < LOGN; ++j)
        for (int i = 0; i < n; ++i) {
            next[i][j] = next[next[i][j - 1]][j - 1];
            f[i][j] = f[i][j - 1] + f[next[i][j - 1]][j - 1];
        }
 
    for (int i = 1; i < n; ++i) {
        ll cur_sum = 0;
        ll cur_ind = i;
 
        for (int j = 0; j < LOGN; ++j)
            if ((res - 1) & (1 << j)) {
                cur_sum += f[cur_ind][j];
                cur_ind = next[cur_ind][j];
            }
        if (cur_sum >= su) {
            cout << res - 1 << '\n';
            return 0;
        }
    }
    cout << res << '\n';

    return 0;
}
