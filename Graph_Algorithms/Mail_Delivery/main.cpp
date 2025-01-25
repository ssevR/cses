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
 
//returns empty vector if path doesnt exist
//directed graph
//no multi edges!!
vector<int> find_euler_path(vector<vector<int> > & g) {
    int n = (int)g.size();
 
    vector<unordered_set<int> > gs(n);
    for (int i = 0; i < n; ++i) {
        for (auto u : g[i]) {
            gs[i].insert(u);
        }
    }
 
    int st = -1;
    int cnt_odd = 0;
    int cnt_edges = 0;
    if (g[0].empty())
        return vector<int>();
 
    for (int i = 0; i < n; ++i) {
        if (g[i].size() % 2) {
            //++cnt_odd;
            //st = i;
            return vector<int>();
        }
        cnt_edges += g[i].size();
    }
    cnt_edges /= 2;
 
    unordered_set<ll> used;
 
    if (cnt_odd > 2) {
        return vector<int>();
    }
    else if (st == -1) {
        for (int i = 0; i < n; ++i) {
            if (g[i].size()) {
                st = i;
                break;
            }
        }
        if (st == -1) {
            return vector<int>();
        }
 
 
    }
 
    stack<int> s;
    s.push(0);
    vector<int> res;
    while(!s.empty()) {
        int v = s.top();
        bool found_edge = false;
        for (auto u : gs[v]) {
 
            s.push(u);
            found_edge = true;
            gs[v].erase(u);
            gs[u].erase(v);
            break;
        }
        if (!found_edge) {
            s.pop();
            res.push_back(v);
        }
    }
 
    if (res.size() == cnt_edges + 1) {
        return res;
    }
    else {
        return vector<int>();
    }
 
}
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<int > > g(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    auto path = find_euler_path(g);
    if (path.empty()) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        for (auto v : path) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }
}
