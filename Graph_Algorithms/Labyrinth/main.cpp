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
int dist[N][N];
pii parent[N][N];
char ch[N][N];
 
bool used[N][N];
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
 
    pii st;
    pii en;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        fill(dist[i], dist[i] + n, INF);
 
        int pos = s[i].find('A');
        if (pos != -1) {
            st = {i, pos};
        }
        
        pos = s[i].find('B');
        if (pos != -1)
            en = {i, pos};
    }
 
 
    queue<pii> q;
    q.push(st);
    used[st.fi][st.se] = 1;
    dist[st.fi][st.se] = 0;
 
    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int tox = x + dx[i];
            int toy = y + dy[i];
            if (0 <= tox && tox < n && 0 <= toy && toy < m && !used[tox][toy] && s[tox][toy] != '#') {
                used[tox][toy] = 1;
                q.push({tox, toy});
                dist[tox][toy] = dist[x][y] + 1;
                parent[tox][toy] = {x, y};
                ch[tox][toy] = C[i];
            }
        }
    }
    if (!used[en.fi][en.se]) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
 
    vector<char> res;
    pii cur = en;
    while(cur != st) {
        res.push_back(ch[cur.fi][cur.se]);
        cur = parent[cur.fi][cur.se];
    }
 
    reverse(res.begin(), res.end());
 
    cout << dist[en.fi][en.se] << '\n';
    for (auto x : res)
        cout << x;
    cout << '\n';

    return 0;
}
