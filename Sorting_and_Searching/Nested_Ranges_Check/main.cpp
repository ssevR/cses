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
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
bool cmp1(pair<pii, int> a, pair<pii, int> b) {
    if (a.fi.fi != b.fi.fi)
        return a.fi.fi < b.fi.fi;
    else
        return a.fi.se > b.fi.se;
}
 
bool cmp2(pair<pii, int> a, pair<pii, int> b) {
    if (a.fi.se != b.fi.se)
        return a.fi.se > b.fi.se;
    else
        return a.fi.se < b.fi.se;
}
 
 
int main() {
    IOS;
 
    int n;
    cin >> n;
    vector<int> f;
    vector<pair<pii, int> > v(n);
 
    for (int i = 0; i < n; ++i) {
        cin >> v[i].fi.fi >> v[i].fi.se;
        f.push_back(v[i].fi.fi);
        f.push_back(v[i].fi.se);
        v[i].se = i;
    }
 
    sort(f.begin(), f.end());
    f.erase(unique(f.begin(), f.end()), f.end());
 
    int sz = f.size();
 
    fenwick_tree <int> fw1(sz), fw2(sz);
 
    for (int i = 0; i < n; ++i) {
        v[i].fi.fi = lower_bound(f.begin(), f.end(), v[i].fi.fi) - f.begin();
        v[i].fi.se = lower_bound(f.begin(), f.end(), v[i].fi.se) - f.begin();
    }
    vector<vector<int> > res(2, vector<int>(n));
 
    sort(v.begin(), v.end(), cmp1);
    for (auto x : v) {
        auto [l, r] = x.fi;
        auto ind = x.se;
        res[1][ind] = fw1.sum(r, sz);
        fw1.add(r, 1);
    }
 
    for (auto x : v) {
        auto [l, r] = x.fi;
        auto ind = x.se;
        fw1.add(r, -1);
        res[0][ind] = fw1.sum(0, r + 1);
    }
 
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < n; ++i) {
            cout << (res[j][i] > 0) << ' ';
        }
        cout << '\n';
    }
}
