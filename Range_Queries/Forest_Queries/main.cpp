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
 
    int n, q;
    cin >> n >> q;
    vector<vector<int> > pr(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) {
            char ca;
            cin >> ca;
            int a = (ca == '*');
            pr[i + 1][j + 1] = pr[i][j + 1] + pr[i + 1][j] - pr[i][j] + a;
        }
 
    while(q--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << pr[y2][x2] - pr[y2][x1 - 1] - pr[y1 - 1][x2] + pr[y1 - 1][x1 - 1] << '\n';
    }
    
}
