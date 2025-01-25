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
 
 
 
#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
 
 
#ifdef _MSC_VER
#include <intrin.h>
#endif
 
#if __cplusplus >= 202002L
#include <bit>
#endif
 
namespace atcoder {
 
namespace internal {
 
#if __cplusplus >= 202002L
 
using std::bit_ceil;
 
#else
 
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}
 
#endif
 
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}
 
constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}
 
}  // namespace internal
 
}  // namespace atcoder
 
 
namespace atcoder {
 
#if __cplusplus >= 201703L
 
template <class S, auto op, auto e> struct segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");
 
#else
 
template <class S, S (*op)(S, S), S (*e)()> struct segtree {
 
#endif
 
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }
 
    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
 
    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }
 
    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;
 
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
 
    S all_prod() const { return d[1]; }
 
    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }
 
    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
 
  private:
    int _n, size, log;
    std::vector<S> d;
 
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};
 
}  // namespace atcoder
 
 
 
using namespace atcoder;
 
// https://atcoder.github.io/ac-library/production/document_en/segtree.html
/* 
segtree<S, op, e>
void seg.set(int p, S x)
S seg.get(int p)
seg.prod(int l, int r)
*/
 
 
 
struct Node{
    int prefix, sufix, mx;
    int prefix0, sufix0, mx0;
    int sz;
 
};
 
Node op(Node a, Node b) {
    Node c;
 
    c.prefix = a.prefix;
    if (a.prefix == a.sz)
        c.prefix += b.prefix;
    c.sufix = b.sufix;
    if (b.sufix == b.sz)
        c.sufix += a.sufix;
    c.mx = max({a.mx, b.mx, a.sufix + b.prefix});
 
    c.prefix0 = a.prefix0;
    if (a.prefix0 == a.sz)
        c.prefix0 += b.prefix0;
    c.sufix0 = b.sufix0;
    if (b.sufix0 == b.sz)
        c.sufix0 += a.sufix0;
    c.mx0 = max({a.mx0, b.mx0, a.sufix0 + b.prefix0});
 
 
    c.sz = a.sz + b.sz;
    return c;
}
 
Node e() { return Node{0, 0, 0, 0}; }
 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    vector<Node> init(n);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0')
            init[i] = Node{0, 0, 0, 1, 1, 1, 1};
        else
            init[i] = Node{1, 1, 1, 0, 0, 0, 1};
    }
    segtree<Node, op, e> seg(init);
 
    int m;
    cin >> m;
    while(m--) {
        int x;
        cin >> x;
        --x;
        if (seg.get(x).mx == 1) 
            seg.set(x, Node{0, 0, 0, 1, 1, 1, 1});
        else 
            seg.set(x, Node{1, 1, 1, 0, 0, 0, 1});
        auto cur = seg.all_prod();
        cout << max(cur.mx, cur.mx0) << ' ';
 
    }
    cout << '\n';
}
