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
 
 
//returns empty vector if path doesnt exist
//directed graph
//no multi edges!!
vector<int> find_euler_path(const vector<vector<int> > & g) {
    int n = (int)g.size();
 
    vector<unordered_set<int> > gs(n);
    vector<int> in(n), out(n);
    int cnt_edges = 0;
    for (int i = 0; i < n; ++i) {
        cnt_edges += g[i].size();
        for (auto u : g[i]) {
            ++out[i];
            ++in[u];
            gs[i].insert(u);
        }
    }
    for (int i = 1; i < n - 1; ++i) {
        if (in[i] != out[i]) {
            return vector<int>();
        }
    }
    if (out[0] - in[0] != 1 || in[n - 1] - out[n - 1] != 1) {
        return vector<int>();
    }
 
    int st = 0;
 
    stack<int> s;
    s.push(st);
    vector<int> res;
    while(!s.empty()) {
        int v = s.top();
        bool found_edge = false;
        for (auto u : gs[v]) {
 
            s.push(u);
            found_edge = true;
            gs[v].erase(u);
            break;
        }
        if (!found_edge) {
            s.pop();
            res.push_back(v);
        }
    }
    reverse(res.begin(), res.end());
 
    if (res.size() == cnt_edges + 1) {
        return res;
    }
    else {
        return vector<int>();
    }
 
}
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
    }
 
    auto res = find_euler_path(g);
    if (!res.empty() && res.front() == 0 && res.back() == n - 1) {
        for (auto v : res)
            cout << v + 1 << ' ';
        cout << '\n';
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
}
