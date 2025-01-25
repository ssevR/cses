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
 
struct line {
    ll k, b;
    ll operator()(const ll x) const {
        return x * k + b;
    }
};
 
struct li_chao {
    vector<line> tree;
    int size;
    int shift;
 
    void init(int n) {
        shift = 1 << (int(log2(n) + 1));
        size = shift * 2;
        tree.assign(size, line{0ll, LINF}); // LINF == 1e18
    }
    void insert(int i, int lx, int rx, line L) {
        if (lx > rx)
            return;
        int mx = (lx + rx) / 2;
        if (L(lx) < tree[i](lx)) 
            swap(L, tree[i]);
        if (lx == rx || L(rx) >= tree[i](rx))
            return;
        if (L(mx) < tree[i](mx)) {
            swap(L, tree[i]);
            insert(2 * i, lx, mx, L);
        }
        else {
            insert(2 * i + 1, mx + 1, rx, L);
        }
 
 
    }
    ll query(int i, int lx, int rx, int pos) {
        if (lx > rx)
            return LINF;
        else if (lx == rx)
            return tree[i](pos);
        int mx = (lx + rx) / 2;
        if (pos <= mx) {
            return min(tree[i](pos), query(2 * i, lx, mx, pos));
        }
        else {
            return min(tree[i](pos), query(2 * i + 1, mx + 1, rx, pos));
        }
    }
    void insert(line L) {
        insert(1, 0, shift - 1, L);
    }
    ll query(int x) {
        return query(1, 0, shift - 1, x);
    }
};
 
 
int main() {
    IOS;
 
    int n, x;
    cin >> n >> x;
    li_chao seg;
    seg.init(x + 1);
    seg.insert({x, 0});
    vector<int> s(n), f(n);
    for (int i = 0; i < n; ++i)
        cin >> s[i];
    for (int i = 0; i < n; ++i)
        cin >> f[i];
    for (int i = 0; i < n - 1; ++i) {
        ll val = seg.query(s[i]);
        seg.insert({f[i], val});
    }
    cout << seg.query(s[n - 1]) << '\n';
}
