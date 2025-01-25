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
 
const int N = 1000 + 5;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int F[N][N];
int h[N], l[N], r[N];
string s[N];
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> s[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            if (s[i][j] == '*')
                h[j] = 0;
            else
                ++h[j];
 
        stack<pii> st;
        st.emplace(-1, -1);
        for (int j = 0; j < m; ++j) {
            while(st.top().fi >= h[j])
                st.pop();
            l[j] = j - st.top().se - 1;
            st.emplace(h[j], j);
        }
        while(!st.empty()) st.pop();
 
        st.emplace(-1, m);
        for (int j = m - 1; j >= 0; --j) {
            while(st.top().fi > h[j])
                st.pop();
            r[j] = st.top().se - j - 1;
            st.emplace(h[j], j);
        }
 
        for (int j = 0; j < m; ++j) {
            ++F[0][0];
            --F[0][min(l[j], r[j]) + 1];
            --F[0][max(l[j], r[j]) + 1];
            ++F[0][l[j] + r[j] + 2];
 
            --F[h[j]][0];
            ++F[h[j]][min(l[j], r[j]) + 1];
            ++F[h[j]][max(l[j], r[j]) + 1];
            --F[h[j]][l[j] + r[j] + 2];
        }
        
    }
 
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            F[i][j] += F[i - 1][j];
    for (int k = 0; k < 2; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 1; j < m; ++j)
                F[i][j] += F[i][j - 1];
 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << F[i][j] << ' ';
        cout << '\n';
    }

    return 0;
}
