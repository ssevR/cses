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
const int dx[8] = {2, 2,1, 1, -2, -2, -1, -1}, dy[8] = {1, -1, 2, -2, 1, -1, 2, -2};
 
const int F = 8;
int res[F][F];
 
int main() {
    vector<unordered_set<int> > g(F * F);
    for (int x = 0; x < F; ++x)
        for (int y = 0; y < F; ++y) {
            for (int i = 0; i < 8; ++i) {
                int tox = x + dx[i];
                int toy = y + dy[i];
                if (0 <= tox && tox < F && 0 <= toy && toy < F) {
                    g[x * F + y].insert(tox * F + toy);
                }
            }
        }
 
    int sx, sy;
    cin >> sy >> sx;
    --sx, --sy;
 
    int cur = 1;
    int x = sx;
    int y = sy;
 
    while(true) {
        res[x][y] = cur++;
        if (cur == 65)
            break;
        int mi = INF;
        int ind;
        for (auto u : g[x * F + y]) {
            if (g[u].size() < mi) {
                mi = g[u].size();
                ind = u;
            }
            g[u].erase(x * F + y);
        }
        g[x * F + y].clear();
        if (mi == INF) { 
            return 1;
        }
 
        x = ind / F;
        y = ind % F;
    } 
 
    for (int i = 0; i < F; ++i) {
        for (int j = 0; j < F; ++j) 
            cout << res[i][j] << ' ';
        cout << '\n';
    }
}
