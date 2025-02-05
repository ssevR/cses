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
//undirected graph
vector<int> find_euler_path(vector<vector<pii> > g, int n, int m, int s) {
    vector<int> path;
    vector<int> used(m);
    stack<int> st;
    st.push(s);
    while(!st.empty()) {
        int v = st.top();
        if (!g[v].empty()) {
            auto [u, idx] = g[v].back();
            g[v].pop_back();
            if (!used[idx]) {
                used[idx] = 1;
                st.push(u);
            }
        }
        else {
            path.push_back(v);
            st.pop();
        }
    }
    if (path.size() != m + 1) 
        path.clear();
    return path;
}
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<pii > > g(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back({u, i});
        g[u].push_back({v, i});
    }
    for (int i = 0; i < n; ++i) {
        if (g[i].size() % 2) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    auto res = find_euler_path(g, n, m, 0);
    if (res.empty()) {
        cout << "IMPOSSIBLE\n";
    }
    for (auto x : res)
        cout << x + 1 << ' ';
    cout << '\n';
}

