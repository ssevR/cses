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
 
 
 
 
#include <cassert>
#include <vector>
 
 
#include <cassert>
#include <numeric>
#include <type_traits>
 
namespace atcoder {
 
namespace internal {
 
#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value ||
                                  std::is_same<T, __int128>::value,
                              std::true_type,
                              std::false_type>::type;
 
template <class T>
using is_unsigned_int128 =
    typename std::conditional<std::is_same<T, __uint128_t>::value ||
                                  std::is_same<T, unsigned __int128>::value,
                              std::true_type,
                              std::false_type>::type;
 
template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value,
                              __uint128_t,
                              unsigned __int128>;
 
template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value ||
                                                  is_signed_int128<T>::value ||
                                                  is_unsigned_int128<T>::value,
                                              std::true_type,
                                              std::false_type>::type;
 
template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                                                 std::is_signed<T>::value) ||
                                                    is_signed_int128<T>::value,
                                                std::true_type,
                                                std::false_type>::type;
 
template <class T>
using is_unsigned_int =
    typename std::conditional<(is_integral<T>::value &&
                               std::is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              std::true_type,
                              std::false_type>::type;
 
template <class T>
using to_unsigned = typename std::conditional<
    is_signed_int128<T>::value,
    make_unsigned_int128<T>,
    typename std::conditional<std::is_signed<T>::value,
                              std::make_unsigned<T>,
                              std::common_type<T>>::type>::type;
 
#else
 
template <class T> using is_integral = typename std::is_integral<T>;
 
template <class T>
using is_signed_int =
    typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                              std::true_type,
                              std::false_type>::type;
 
template <class T>
using is_unsigned_int =
    typename std::conditional<is_integral<T>::value &&
                                  std::is_unsigned<T>::value,
                              std::true_type,
                              std::false_type>::type;
 
template <class T>
using to_unsigned = typename std::conditional<is_signed_int<T>::value,
                                              std::make_unsigned<T>,
                                              std::common_type<T>>::type;
 
#endif
 
template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;
 
template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;
 
template <class T> using to_unsigned_t = typename to_unsigned<T>::type;
 
}  // namespace internal
 
}  // namespace atcoder
 
 
namespace atcoder {
 
template <class T> struct fenwick_tree {
    using U = internal::to_unsigned_t<T>;
 
  public:
    fenwick_tree() : _n(0) {}
    explicit fenwick_tree(int n) : _n(n), data(n) {}
 
    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += U(x);
            p += p & -p;
        }
    }
 
    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }
 
  private:
    int _n;
    std::vector<U> data;
 
    U sum(int r) {
        U s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};
 
}  // namespace atcoder
 
 
 
using namespace atcoder;
// https://atcoder.github.io/ac-library/production/document_en/fenwicktree.html
/*
fenwick_tree<long long> fw(n);
fw.add(i, a);
fw.sum(l, r);
*/
 
const int N = (1 << 19);
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    int n;
    cin >> n;
    vector<int> f;
    f.reserve(4 * n);
    vector<pair<int, pii> > h, v;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        f.push_back(x1);
        f.push_back(y1);
        f.push_back(x2);
        f.push_back(y2);
        if (x1 == x2) {
            v.emplace_back(x1, mp(min(y1, y2), max(y1, y2)));
        }
        else {
            h.emplace_back(y1, mp(min(x1, x2), max(x1, x2)));
        }
    }
    sort(f.begin(), f.end());
    f.erase(unique(f.begin(), f.end()), f.end());
    vector<pii> X[N];
    for (auto& cur : v) {
        cur.fi = lower_bound(f.begin(), f.end(), cur.fi) - f.begin();
        cur.se.fi = lower_bound(f.begin(), f.end(), cur.se.fi) - f.begin();
        cur.se.se = lower_bound(f.begin(), f.end(), cur.se.se) - f.begin();
        X[cur.se.fi].push_back({cur.fi, 1});
        X[cur.se.se + 1].push_back({cur.fi, -1});
    }
    for (auto & cur : h) {
        cur.fi = lower_bound(f.begin(), f.end(), cur.fi) - f.begin();
        cur.se.fi = lower_bound(f.begin(), f.end(), cur.se.fi) - f.begin();
        cur.se.se = lower_bound(f.begin(), f.end(), cur.se.se) - f.begin();
    }
    sort(h.begin(), h.end());
    fenwick_tree<int> fw(N);
    ll res = 0;
    for (int i = 0, cur = 0; i < h.size(); ++i) {
        while(cur <= h[i].fi) {
            for (auto& p : X[cur]) {
                fw.add(p.fi, p.se);
            }
            ++cur;
        }
        res += fw.sum(h[i].se.fi, h[i].se.se + 1);
    }
    cout << res << '\n';

    return 0;
}
