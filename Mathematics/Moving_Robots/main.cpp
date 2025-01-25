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
const int K = 101;
 
ld res[8][8];
 
ld cur[2][8][8];
 
 
int main() {
    for (int i = 0; i < 8; ++i)
        fill(res[i], res[i] + 8, 1);
 
    int k;
    cin >> k;
    for (int x1 = 0; x1 < 8; ++x1)
        for (int y1 = 0; y1 < 8; ++y1) {
            for (int i = 0; i < 8; ++i)
                fill(cur[0][i], cur[0][i] + 8, 0);
 
            cur[0][x1][y1] = 1;
            for (int z = 1; z <= k; ++z) {
                for (int i = 0; i < 8; ++i)
                    fill(cur[z&1][i], cur[z&1][i] + 8, 0.0);
 
                for (int i = 0; i < 8; ++i)
                    for (int j = 0; j < 8; ++j) {
                        int cnt = 4;
                        if (i == 0 || i == 7)
                            --cnt;
                        if (j == 0 || j == 7)
                            --cnt;
                        for (int d = 0; d < 4; ++d) {
                            int toi = i + dx[d];
                            int toj = j + dy[d];
                            if (0 <= toi && toi < 8 && 0 <= toj && toj < 8) {
                                cur[z&1][toi][toj] += cur[(z + 1)&1][i][j]/cnt;
                            }
                        }
                    }
            }
            ld tmp = 0;
            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 8; ++j) {
                    res[i][j] *= (1 - cur[k&1][i][j]);
                    tmp += cur[k&1][i][j];
                }
        }
    ld ans = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            ans += res[i][j];
    cout << fixed << setprecision(6) << ans << '\n';

    return 0;
}
