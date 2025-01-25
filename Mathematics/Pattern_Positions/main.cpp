#pragma GCC optimize("O3")
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define IOS ios::sync_with_stdio(false); cin.tie(0)
#define ll long long
#define ld long double
#define rep(i,a,n) for (int i=(int)(a);i<(int)(n);i++)
#define per(i,a,n) for (int i=(int)(n-1);i>=(int)(a);i--)
#define mp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define fi first
#define se second
 
 
const int MOD = 1e9+7; // 998244353; // = (119<<23)+1
const int MX = 2e5+5;
const ll INF = 1e9;
const ld PI = 4*atan((ld)1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
 
 
 
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
 
 
int op(int a, int b) { return min(a, b); }
 
int e() { return INF; }
 
 
template <typename T>
using ordered_set =
tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
void radix_sort(vector<pair<pii, int> >& v) {
    int n = v.size();
    {
        vector<int> cnt(n);
        for (int i = 0; i < n; ++i) {
            ++cnt[v[i].first.second];
        }
 
        vector<int> pos(n);
        for (int i = 1; i < n; ++i) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
 
        vector<pair<pii, int> > v_new(n);
        for (int i = 0; i < n; ++i) {
            v_new[pos[v[i].first.second]] = v[i];
            ++pos[v[i].first.second];
        }
        v = v_new;
    }
 
    {
        vector<int> cnt(n);
        for (int i = 0; i < n; ++i) {
            ++cnt[v[i].first.first];
        }
 
        vector<int> pos(n);
        for (int i = 1; i < n; ++i) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
 
        vector<pair<pii, int> > v_new(n);
        for (int i = 0; i < n; ++i) {
            v_new[pos[v[i].first.first]] = v[i];
            ++pos[v[i].first.first];
        }
        v = v_new;
    }
}
 
int main() {
    IOS;
    string s;
    cin >> s;
 
    s += '#';
    int n = s.size();
 
 
    vector<pair<pii, int> > v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = {{s[i], s[i]}, i};
    }
 
    vector<int> c(n);
 
 
    sort(v.begin(), v.end());
 
    for (int i = 0; (1 << i) <= n; ++i) {
 
        int cnt_class = 0;
        pii last = v[0].first;
        for (int j = 0; j < n; ++j) {
            if (v[j].first.first != last.first || v[j].first.second != last.second) {
                ++cnt_class;
            }
            last = v[j].first;
            v[j].first.first = cnt_class;
        }
 
        for (int j = 0; j < n; ++j) {
            c[v[j].second] = v[j].first.first;
        }
 
        for (int j = 0; j < n; ++j) {
            v[j].first.second = c[(v[j].second + (1 << i)) % n];
        }
        radix_sort(v);
    }
    vector<int> suf_arr(n);
    for (int i = 0; i < n; ++i) {
        suf_arr[i] = v[i].second;
    }
 
    segtree<int, op, e> seg(suf_arr);
 
    int q;
    cin >> q;
    while(q--) {
        string p;
        cin >> p;
        int len = p.size();
 
        int l = -1, r = n;
        while(l + 1 < r) {
            int med = (l + r) / 2;
            if (s.substr(suf_arr[med], len) < p) {
                l = med;
            }
            else {
                r = med;
            }
        }
        int left = l;
 
        l = -1, r = n;
        while(l + 1 < r) {
            int med = (l + r) / 2;
            if (s.substr(suf_arr[med], len) <= p) {
                l = med;
            }
            else {
                r = med;
            }
        }
 
        int right = l;
        if (left == right)
            cout << "-1\n";
        else  {
            cout << seg.prod(left + 1, right + 1) + 1 << '\n';
        }
    }

    return 0;
}
