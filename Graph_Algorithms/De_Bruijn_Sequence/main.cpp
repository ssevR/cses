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
            break;
        }
        if (!found_edge) {
            s.pop();
            res.push_back(v);
        }
    }
 
    return res;
 
}
 
int main() {
    IOS;
    int n;
    cin >> n;
    if (n == 1) {
        cout << "01\n";
        return 0;
    }
 
    vector<vector<int> > g(1 << (n - 1));
    for (int i = 0; i < (1 << (n - 1)); ++i) {
        int tmp = (i * 2) & ((1 << (n - 1)) - 1);
        g[i].push_back(tmp);
        g[i].push_back(tmp + 1);
    }
 
    auto res = find_euler_path(g);
 
    for (int i = 0; i < res.size(); ++i) {
        cout << (res[i]&1);
    }
    for (int i = 0; i < n - 2; ++i) {
        cout << 0;
    }
    cout << '\n';
}
