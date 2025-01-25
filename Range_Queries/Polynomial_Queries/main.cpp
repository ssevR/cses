#pragma GCC optimize("O2")
 
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
 
 
struct seg_tree {
    struct Node {
        ll val = 0;
        ll a = 0;
        ll b = 0;
        int siz = 0;
    };
 
    vector<Node> tree;
    int size;
    int shift;
 
    void init(vector <int> a) {
        shift = (1 << int(log2(a.size()) + 1));
        size = shift * 2;
        tree.assign(size, Node{0, 0, 0, 0} );
        for (int i = shift; i < shift * 2; ++i) {
            if (i - shift < a.size())
                tree[i] = {a[i - shift], 0, 0, 1};
        }
        for (int i = shift - 1; i > 0; --i) {
            tree[i].siz = tree[i * 2].siz + tree[i * 2 + 1].siz;
            tree[i].val = tree[i * 2].val + tree[i * 2 + 1].val;
        }
    }
 
    void push(int x) {
        ll a = tree[x].a;
        ll b = tree[x].b;
        tree[x].val += tree[x].siz * b + a * tree[x].siz * (tree[x].siz + 1) / 2; 
        tree[x].a = tree[x].b = 0;
 
        if (x >= shift)
            return;
 
        tree[x * 2].a += a;
        tree[x * 2].b += b;
 
        tree[x * 2 + 1].a += a;
        tree[x * 2 + 1].b += b + tree[x * 2].siz * a;
 
        return;
    }
 
    void add(int l, int r, ll a, ll b, int x, int lx, int rx) {
        push(x);
        if (r < lx || l > rx || lx > rx) {
            return;
        }
 
        if (l <= lx && rx <= r) {
            tree[x].a = a;
            tree[x].b = b;
            return;
        }
 
        int mx = (lx + rx) / 2;
        add(l, r, a, b, x * 2, lx, mx);
        int inter = max(0, min(r, mx) -  max(l, lx) + 1);
        add(l, r, a, b + inter * a, x * 2 + 1, mx + 1, rx);
 
        push(2 * x);
        push(2 * x + 1);
        tree[x].val = tree[x * 2].val + tree[x * 2 + 1].val;
    }
 
    long long query(int l, int r, int x, int lx, int rx) {
        push(x);
        if (r < lx || l > rx || lx > rx) {
            return 0;
        }
 
        if (l <= lx && rx <= r) {
            return tree[x].val;
        }
 
        int mx = (lx + rx) / 2;
 
        return query(l, r, x * 2, lx, mx) + query(l, r, x * 2 + 1, mx + 1, rx);
    }
};
 
 
namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return; write<T>(x / 10), putchar((x % 10) ^ '0'); }
	template <typename T> inline void print(T x) { if (x > 0) write<T>(x); else if (x < 0) putchar('-'), write<T>(-x); else putchar('0'); }
	template <typename T> inline void print(T x, char en) { print<T>(x), putchar(en); }
}; using namespace FastIO;
 
 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    int n = read<int>(), q = read<int>();
 
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        a[i] = read<int>();
    seg_tree seg;
    seg.init(a);
    while(q--) {
        int t = read<int>(), l = read<int>(), r = read<int>();
        --l, --r;
 
        if (t == 1) {
            seg.add(l, r, 1, 0, 1, 0, seg.shift - 1);
        }
        else {
            print<ll>(seg.query(l, r, 1, 0, seg.shift - 1), '\n');
        }
    }

    return 0;
}
