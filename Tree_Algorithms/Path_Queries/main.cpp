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
 
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector <int> v(n);
    vector<vector<int> > g(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    int timer = 0;
    vector<int> beg(n), end(n);
    auto dfs = [&](int v, int p, auto&& dfs) -> void {
        beg[v] = timer++;
        for (auto u : g[v]) {
            if (u != p)
                dfs(u, v, dfs);
        }
        end[v] = timer++;
    };
    dfs(0, -1, dfs);
    fenwick_tree<ll> fw(timer);
    for (int i = 0; i < n; ++i) {
        fw.add(beg[i], v[i]);
        fw.add(end[i], -v[i]);
    }
    while(q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int ind, val;
            cin >> ind >> val;
            --ind;
            fw.add(beg[ind], val - v[ind]);
            // -v[ind] -> -val
            fw.add(end[ind], -(val - v[ind]));
 
            v[ind] = val;
        }
        else {
            int ind;
            cin >> ind;
            --ind;
            cout << fw.sum(0, beg[ind] + 1) << '\n';
        }
    }

    return 0;
}
