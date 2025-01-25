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
 
const int N = 5e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dy[4] = {1,0,-1,0}, dx[4] = {0,1,0,-1};
 
int op(int a, int b) { return min(a, b); }
 
int e() { return INF; }
ll res = 0;
 
struct line {
    ll y1, x1, y2, x2;
};
 
struct seg {
    int prim, l, r, ind;
    bool operator<(const seg& rhs) const {
        if(prim != rhs.prim)
            return prim < rhs.prim;
        if(l != rhs.l)
            return l < rhs.l;
        if(r != rhs.r)
            return r < rhs.r;
        return ind < rhs.ind;
    }
};
 
 
int main() {
    IOS;
    int w[256];
    w['U'] = 0;
    w['R'] = 1;
    w['D'] = 2;
    w['L'] = 3;
 
    int n;
    cin >> n;
    ll y = 0;
    ll x = 0;
    vector<line> g(n);
    vector<ll> f;
    f.reserve(4 * n);
    vector<char>ch(n);
    for (int i = 0; i < n; ++i) {
        int cur;
        cin >> ch[i] >> cur;
        if (i == n - 1)
            ++cur;
 
        ll next_y = y + dy[w[ch[i]]] * (cur - 1);
        ll next_x = x + dx[w[ch[i]]] * (cur - 1);
        g[i] = {y, x, next_y, next_x};
        f.push_back(y);
        f.push_back(x);
        f.push_back(next_y);
        f.push_back(next_x);
        y = next_y + dy[w[ch[i]]];
        x = next_x + dx[w[ch[i]]];
    }
    sort(f.begin(), f.end());
    f.erase(unique(f.begin(), f.end()), f.end());
 
    vector<seg> h, v, p;
 
    for (int i = 0; i < n; ++i) {
        line cur = g[i];
        cur.y1 = lower_bound(f.begin(), f.end(), cur.y1) - f.begin();
        cur.x1 = lower_bound(f.begin(), f.end(), cur.x1) - f.begin();
        cur.y2 = lower_bound(f.begin(), f.end(), cur.y2) - f.begin();
        cur.x2 = lower_bound(f.begin(), f.end(), cur.x2) - f.begin();
        if (cur.x1 == cur.x2) {
            //ind 
            v.push_back({min(cur.y1, cur.y2), 1, cur.x1, i});
            v.push_back({max(cur.y1, cur.y2) + 1, 0, cur.x1, i});
        }
        else {
            h.push_back({cur.y1, min(cur.x1, cur.x2), max(cur.x1, cur.x2), i});
            p.push_back({min(cur.x1, cur.x2), 1, cur.y1, i});
            p.push_back({max(cur.x1, cur.x2) + 1, 0, cur.y1, i});
        }
    }
    sort(h.begin(), h.end());
    sort(v.begin(), v.end());
    sort(p.begin(), p.end());
    int sz = f.size() + 5;
    vector<set<int> > s(sz), q(sz);;
    segtree<int, op, e> tr(sz);
    int mi_ind = n - 1;
 
    for (int i = 0, j = 0; i < h.size(); ++i) {
        while(j < v.size() && v[j].prim <= h[i].prim) {
            if (v[j].l == 1) { //add v[j].ind to v[j].r
                if (!s[v[j].r].empty()) {
                    mi_ind = min(mi_ind, max(v[j].ind, *s[v[j].r].begin()));
                }
                s[v[j].r].insert(v[j].ind);
            }
            else {
                s[v[j].r].erase(v[j].ind);
            }
            int val = s[v[j].r].empty() ? INF : (*s[v[j].r].begin());
            tr.set(v[j].r, val);
 
            ++j;
        }
        mi_ind = min(mi_ind, max(h[i].ind, tr.prod(h[i].l, h[i].r + 1)));
    }
    for (int j = 0; j < p.size(); ++j) {
        if (p[j].l == 1) { //add p[j].ind to p[j].r
            if (!q[p[j].r].empty()) {
                mi_ind = min(mi_ind, max(p[j].ind, *q[p[j].r].begin()));
            }
            q[p[j].r].insert(p[j].ind);
        }
        else {
            q[p[j].r].erase(p[j].ind);
        }
    }
 
    ll len = abs(g[mi_ind].x1 - g[mi_ind].x2) + abs(g[mi_ind].y1 - g[mi_ind].y2);
    ll mi = len;
    for (int i = 0; i < mi_ind; ++i) {
        // intersect g[mi_ind] with g[i]
        if (g[mi_ind].x1 == g[mi_ind].x2 && g[i].x1 == g[i].x2) { // vert vert
            if (g[mi_ind].x1 == g[i].x1) {
                ll Y1 = min(g[i].y1, g[i].y2);
                ll Y2 = max(g[i].y1, g[i].y2);
                ll inter = min(max(g[mi_ind].y1, g[mi_ind].y2), Y2) -
                            max(min(g[mi_ind].y1, g[mi_ind].y2), Y1) + 1;
                if (inter <= 0)
                    continue;
                if(Y1 <= g[mi_ind].y1 && g[mi_ind].y1 <= Y2) {
                    mi = 0;
                }
                else {
                    mi = min({mi, abs(g[mi_ind].y1 - Y1), abs(g[mi_ind].y1 - Y2)});
                }
            }
        }
        else if (g[mi_ind].y1 == g[mi_ind].y2 && g[i].y1 == g[i].y2) { // hor hor
            if (g[mi_ind].y1 == g[i].y1) {
                ll X1 = min(g[i].x1, g[i].x2);
                ll X2 = max(g[i].x1, g[i].x2);
                ll inter = min(max(g[mi_ind].x1, g[mi_ind].x2), X2) -
                            max(min(g[mi_ind].x1, g[mi_ind].x2), X1) + 1;
                if (inter <= 0)
                    continue;
                if(X1 <= g[mi_ind].x1 && g[mi_ind].x1 <= X2) {
                    mi = 0;
                }
                else {
                    mi = min({mi, abs(g[mi_ind].x1 - X1), abs(g[mi_ind].x1 - X2)});
                }
            }
        }
        else {
            auto hor = g[mi_ind];
            auto vert = g[i];
            if (hor.y1 != hor.y2) {
                swap(hor, vert);
            }
            if (hor.x1 > hor.x2)
                swap(hor.x1, hor.x2);
            if (vert.y1 > vert.y2)
                swap(vert.y1, vert.y2);
            ll y = hor.y1;
            ll x = vert.x1;
            if(hor.x1 <= x && x <= hor.x2 && vert.y1 <= y && y <= vert.y2) {
                mi = min(mi, abs(g[mi_ind].x1 - x) + abs(g[mi_ind].y1 - y));
            }
 
        }
    }
    res = mi;
    for (int i = 0; i < mi_ind; ++i) {
        if (i)
            res += 1;
        res += abs(g[i].x1 - g[i].x2) + abs(g[i].y1 - g[i].y2);
    }
    if(mi_ind) res += 1;
 
    for (int i = 1; i <= mi_ind; ++i) {
        if (ch[i] + ch[i - 1] == 'R' + 'L' ||
            ch[i] + ch[i - 1] == 'D' + 'U')
            res -= mi;
    }
    cout << res << '\n';

    return 0;
}
