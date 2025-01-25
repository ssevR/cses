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
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
    }
 
    auto find_cycles = [&]() ->vector<vector<int> >  {
        vector<vector<int> > cycles;
        vector<int> used(n);
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                int cur = i;
                vector<int> v;
                while(!used[cur]) {
                    v.push_back(cur);
                    used[cur] = 1;
                    cur = p[cur];
                }
                if (v.size() > 1)
                    cycles.push_back(v);
            }
        }
        return cycles;
    };
 
    auto v = find_cycles();
    if (v.empty()) {
        cout << 0 << '\n';
        return 0;
    }
 
    int flag = 0;
    for (auto x : v) {
        if (x.size() != 2)
            flag = 1;
    }
    if (!flag) {
        cout << 1 << '\n';
        cout << v.size() << '\n';
        for (auto x : v)
            cout << x[0] + 1 << ' ' << x[1] + 1 << '\n';
        return 0;
    }
 
    vector<pii> res1;
 
    for (auto x : v) {
        if (x.size() == 2) 
            continue;
        for (int i = 0, j = (int)x.size() - 2; i < j; ++i, --j) {
            res1.emplace_back(x[i], x[j]);
            swap(p[x[i]], p[x[j]]);
        }
    }
    v = find_cycles();
    flag = 0;
    for (auto x : v) {
        if (x.size() != 2)
            flag = 1;
    }
    if (!flag) {
        cout << 2 << '\n';
        cout << res1.size() << '\n';
        for (auto x : res1)
            cout << x.fi + 1 << ' ' << x.se + 1 << '\n';
        cout << v.size() << '\n';
        for (auto x : v)
            cout << x[0] + 1 << ' ' << x[1] + 1 << '\n';
        return 0;
    }
    else {
        return 1;
    }
}
