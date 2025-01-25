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
const int M = 19;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
struct Node{
    int l, r;
    Node* next[M];
 
    Node() {
        fill(next, next + M, nullptr);
    }
};
 
int main() {
    IOS;
 
    int n, q;
    cin >> n >> q;
    vector<Node> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].l >> v[i].r;
    }
    sort(v.begin(), v.end(), [](Node& a, Node& b) {
        return a.r < b.r;
    });
    for (int i = 0, j = 0; i < n && j < n;) {
        if (v[i].r > v[j].l)
            ++j;
        else {
            v[i].next[0] = &v[j];
            ++i;
        }
    }
    for (int j = 1; j < M; ++j)
        for (int i = 0; i < n; ++i)
            if (v[i].next[j - 1])
                v[i].next[j] = (v[i].next[j - 1])->next[j - 1];
    vector<pair<pii, int> > queries(q);
    vector<int> res(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].fi.fi >> queries[i].fi.se;
        queries[i].se = i;
    }
    sort(queries.begin(), queries.end());
 
    int i = 0;
    for (auto& x : queries) {
        auto [l, r] = x.fi;
        auto ind = x.se;
        while(i < n && v[i].l < l)
            ++i;
        if (i == n || v[i].r > r) {
            res[ind] = 0;
            continue;
        }
        res[ind] = 0;
        auto cur = &v[i];
        for (int j = M - 1; j >= 0; --j) {
            if (cur->next[j] && cur->next[j]->r <= r) {
                res[ind] |= (1 << j);
                cur = cur->next[j];
            }
        }
        ++res[ind];
    }
    for (auto x : res)
        cout << x << '\n';

    return 0;
}
