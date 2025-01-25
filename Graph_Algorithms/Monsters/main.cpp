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
 
 
const int N = 1e3 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const int C[4] = {'D', 'R', 'U', 'L'};
string s[N];
 
int dist[2][N][N];
int used[2][N][N];
 
pii parent[N][N];
char ch[N][N];
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int z = 0; z < 2; ++z)
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j)
            dist[z][i][j] = INF;
 
 
    queue<pii> q[2];
    pii st;
 
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == 'M') {
                q[0].push({i, j});
                dist[0][i][j] = 0;
                used[0][i][j] = 1;
            }
            if (s[i][j] == 'A') {
                q[1].push({i, j});
                dist[1][i][j] = 0;
                used[1][i][j] = 1;
                st = {i, j};
            }
        }
    }
 
    while(!q[0].empty()) {
        auto [x, y] = q[0].front();
        q[0].pop();
 
        for (int i = 0; i < 4; ++i) {
            int tox = x + dx[i];
            int toy = y + dy[i];
            if (0 <= tox && tox < n && 0 <= toy && toy < m && !used[0][tox][toy] && s[tox][toy] != '#') {
                dist[0][tox][toy] = dist[0][x][y] + 1;
                used[0][tox][toy] = 1;
                q[0].push({tox, toy});
            }
        }
    }
 
    int is_good = 0;
    pii good;
 
    while(!q[1].empty()) {
        auto [x, y] = q[1].front();
        q[1].pop();
        if (x == 0 || x == n - 1 || y == 0 || y == m - 1) {
            is_good = 1;
            good = {x, y};
        }
        for (int i = 0; i < 4; ++i) {
            int tox = x + dx[i];
            int toy = y + dy[i];
 
            if (0 <= tox && tox < n && 0 <= toy && toy < m && !used[1][tox][toy] && s[tox][toy] != '#'
                && dist[1][x][y] + 1 < dist[0][tox][toy]) {
                dist[1][tox][toy] = dist[1][x][y] + 1;
                used[1][tox][toy] = 1;
                q[1].push({tox, toy});
 
                parent[tox][toy] = {x, y};
                ch[tox][toy] = C[i];
 
            }
        }
    }
    if (!is_good) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
 
    vector<char> res;
 
    auto cur = good;
    while(cur != st) {
        res.push_back(ch[cur.fi][cur.se]);
        cur = parent[cur.fi][cur.se];
    }
 
    reverse(res.begin(), res.end());
    cout << res.size() << '\n';
    for (auto x : res) {
        cout << x;
    }
    cout << '\n';

    return 0;
}
