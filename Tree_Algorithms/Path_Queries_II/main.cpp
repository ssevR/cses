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
 
 
int op(int a, int b) { return max(a, b); }
 
int e() { return -1; }
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 2e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
int up[N][19];
int lvl[N], a[N], label[N], sz[N], top[N];
vector<int> g[N];
 
 
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
 
    for (int i = 1; i < n; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    up[0][0] = n;
    up[n][0] = n;
    auto dfs1 = [&](int v, auto&& dfs1) -> void {
        sz[v] = 1;
        for (auto u : g[v]) {
            if (u == up[v][0])
                continue;
            lvl[u] = lvl[v] + 1;
            up[u][0] = v;
            dfs1(u, dfs1);
            sz[v] += sz[u];
            
        }
        return;
    };
    dfs1(0, dfs1);
    int timer = 0;
    auto dfs2 = [&](int v, auto&& dfs2) -> void {
        label[v] = timer++;
        for (auto u : g[v]) {
            if (u == up[v][0] || sz[u] * 2 < sz[v])
                continue;
            top[u] = top[v];
            dfs2(u, dfs2);
        }
        for (auto u: g[v]) {
            if (u == up[v][0] || sz[u] * 2 >= sz[v])
                continue;
            top[u] = u;
            dfs2(u, dfs2);
        }
    };
    dfs2(0, dfs2);
 
    for (int j = 1; j < 19; ++j)
        for (int i = 0; i < n + 1; ++i)
            up[i][j] = up[up[i][j - 1]][j - 1];
 
    vector<int> init(n);
    for (int i = 0; i < n; ++i) 
        init[label[i]] = a[i];
    segtree<int, op, e> seg(init);
 
    while(q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            --s;
            seg.set(label[s], x);
            a[s] = x;
        }
        else {
            int v, u;
            cin >> v >> u;
            --v, --u;
            int cp_v = v, cp_u = u;
 
            if (lvl[u] > lvl[v])
                swap(v, u);
 
            int k = lvl[v] - lvl[u];
            int lca = 0;
            for (int i = 0; i < 19; ++i) {
                if (k & (1 << i))
                    v = up[v][i];
            }
            if (v == u) {
                lca = v;
            }
            else {
                for (int i = 18; i >= 0; --i) {
                    if (up[v][i] != up[u][i]) {
                        v = up[v][i];
                        u = up[u][i];
                    }
                }
                lca = up[v][0];
            }
            swap(cp_v, v);
            swap(cp_u, u);
            int mx = a[lca];
 
            for (int cur : {v, u}) {
                while(cur != n && lvl[cur] - lvl[lca] > 0) {
                    int top_v = top[cur];
                    if (top[cur] == cur)
                        mx = max(mx, a[cur]);
                    else
                        mx = max(mx, seg.prod(max(label[lca] + 1, label[top[cur]]), label[cur] + 1)); 
                    cur = up[top[cur]][0];
                }
            }
            cout << mx << ' ';
        }
    }
    cout << '\n';

    return 0;
}
