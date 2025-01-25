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
const int M = 21;
const int F = (1 << M);
 
struct Node {
    int add = 0;
    int mi = 0;
    int cnt = 0;
};
 
Node tree[(1 << (M + 1))];
 
 
// https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/C
 
struct seg_tree {
    int size;
    int shift;
 
    void init() {
        shift = F;
        size = shift * 2;
        fill(tree + shift, tree + size, Node{0, 0, 1});
        for (int i = shift - 1; i >= 1; --i) {
            tree[i].cnt = tree[i * 2].cnt + tree[i * 2 + 1].cnt;
        }
    }
 
 
    void push(int x) {
        if (tree[x].add == 0 || x >= shift) {
            tree[x].add = 0;
            return;
        }
 
        tree[x * 2].add += tree[x].add;
        tree[x * 2 + 1].add += tree[x].add;
        tree[x * 2].mi += tree[x].add;
        tree[x * 2 + 1].mi += tree[x].add;
 
        tree[x].add = 0;
    }
 
    void add(int l, int r, int val, int x, int lx, int rx) {
        push(x);
        if (r < lx || l > rx || lx > rx) {
            return;
        }
 
        if (l <= lx && rx <= r) {
            tree[x].add = val;
            tree[x].mi += val;
            return;
        }
 
        int mx = (lx + rx) / 2;
        add(l, r, val, x * 2, lx, mx);
        add(l, r, val, x * 2 + 1, mx + 1, rx);
        tree[x].mi = min(tree[x * 2].mi, tree[x * 2 + 1].mi);
        tree[x].cnt = 0;
        if (tree[x].mi == tree[x * 2].mi)
            tree[x].cnt += tree[x * 2].cnt;
        if (tree[x].mi == tree[x * 2 + 1].mi)
            tree[x].cnt += tree[x * 2 + 1].cnt;
    }
    void add(int l, int r, int val) {
        return add(l, r, val, 1, 0, shift - 1);
    }
 
};
 
 
struct line {
    int x, val, y1, y2;
    bool operator<(const line& rhs) const {
        if (x != rhs.x)
            return x < rhs.x;
        if (val != rhs.val)
            return val < rhs.val;
        if (y1 != rhs.y1)
            return y1 < rhs.y1;
        return y2 < rhs.y2;
    }
};
 
int main() {
    IOS;
    int n;
    cin >> n;
    seg_tree seg;
    seg.init();
    vector<line> op;
    op.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += F/2;
        y1 += F/2;
        x2 += F/2;
        y2 += F/2;
        op.push_back({x1, 1, y1, y2 - 1});
        op.push_back({x2, -1, y1, y2 - 1});
    }
    sort(op.begin(), op.end());
    ll res = 0;
    for (int i = 0, j = 0; i < 2 * F; ++i) {
        while(j < int(op.size()) && op[j].x <= i) {
            seg.add(op[j].y1, op[j].y2, op[j].val);
            ++j;
        }
        res += F - tree[1].cnt;
    }
    cout << res << '\n';

    return 0;
}
