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
    int n;
    cin >> n;
    vector<int>k(n);
    for (int i = 0; i < n; ++i)
        cin >> k[i];
    vector<int> prev(n), next(n);
 
 
    stack<pii> st;
    st.push({0, -1});
    for (int i = 0; i < n; ++i) {
        while(k[i] <= st.top().fi)
            st.pop();
        prev[i] = st.top().se;
        st.emplace(k[i], i);
    }
 
    while(!st.empty())
        st.pop();
    st.push({0, n});
    for (int i = n - 1; i >= 0; --i) {
        while(k[i] <= st.top().fi)
            st.pop();
        next[i] = st.top().se;
        st.emplace(k[i], i);
    }
 
    ll res = 0;
    for (int i = 0; i < n; ++i)
        res = max(res, 1ll * k[i] * (next[i] - prev[i] - 1));
    cout << res << '\n';

    return 0;
}
