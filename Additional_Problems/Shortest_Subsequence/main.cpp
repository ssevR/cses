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
 
 
int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    char c[256];
    c['A'] = 0;
    c['C'] = 1;
    c['G'] = 2;
    c['T'] = 3;
    int f[4] = {'A', 'C', 'G', 'T'};
    
    for (int i = 0; i <= n;) {
        int ind = 0, mx = -1;
 
        for (int j = 0; j < 4; ++j) {
            int cur = find(s.begin() + i, s.end(), char(f[j])) - s.begin();
            if (cur > mx) {
                mx = cur;
                ind = j;
            }
        }
        cout << char(f[ind]);
        i = mx + 1;
    }
    cout << '\n';

    return 0;
}
