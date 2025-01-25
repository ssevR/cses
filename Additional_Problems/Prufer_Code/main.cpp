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
    vector <int> cnt(n);
    vector<int> a(n - 2);
    for (int i = 0; i < n - 2; ++i) {
        cin >> a[i];
        --a[i];
        ++cnt[a[i]];
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; ++i)
        if (!cnt[i])
            q.push(i);
    vector <pii> edges;
    for (int i = 0; i < n - 2; ++i) {
        int v = q.top();
        q.pop();
        edges.emplace_back(v, a[i]);
        --cnt[a[i]];
        if (cnt[a[i]] == 0)
            q.push(a[i]);
    }
    int v = q.top();
    q.pop();
    int u = q.top();
    edges.emplace_back(v, u);
    for (auto x : edges)
        cout << x.fi + 1 << ' ' << x.se + 1 << '\n';

    return 0;
}
