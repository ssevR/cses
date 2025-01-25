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
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    vector<int> f(m);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        stack<pii> st;
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '*')
                f[j] = 0;
            else 
                ++f[j];
        }
 
        vector<int> prev(m);
        vector<int> next(m);
        st.emplace(-1, -1);
 
        for (int j = 0; j < m; ++j) {
            while(st.top().fi >= f[j])
                st.pop();
            prev[j] = st.top().se;
            st.emplace(f[j], j);
        }
        while(!st.empty())
            st.pop();
 
        st.emplace(-1, m);
        for (int j = m - 1; j >= 0; --j) {
            while(st.top().fi >= f[j])
                st.pop();
            next[j] = st.top().se;
            st.emplace(f[j], j);
        }
 
        for (int j = 0; j < m; ++j) {
            res = max(res, (next[j] - prev[j] - 1) * f[j]);
        }
    }
    cout << res << '\n';

    return 0;
}
