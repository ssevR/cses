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
 
 
//source: https://cp-algorithms.com/sequences/longest_increasing_subsequence.html
//checker: https://judge.yosupo.jp/problem/longest_increasing_subsequence
//const int INF = 1e9 + 100;
 
// return indexes
vector<int> calc_lis(const vector<int>& x) {
    int n = x.size();
    vector<pair<int, int> > dp(n, make_pair(INF, INF));
    //vector<int> res(n); //see lis.cpp
 
    vector<int> prev(n, -1);
 
    for (int i = 0; i < n; ++i) {
        int ind = lower_bound(dp.begin(), dp.end(), make_pair(x[i], -INF)) - dp.begin();
        dp[ind] = make_pair(x[i], i);
        if (ind) {
            prev[i] = dp[ind - 1].second;
        }
    }
 
    int len = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i].first < INF) {
            len = i + 1;
        }
    }
 
    vector<int> lis;
 
    int cur = dp[len - 1].second;
    while(cur != -1) {
        lis.push_back(cur);
        cur = prev[cur];
    }
    reverse(lis.begin(), lis.end());
 
    return lis;
}
 
int main() {
    IOS;
    int n;
    cin >> n;
    vector<int>p(n), w(n);
    fenwick_tree<int> fw(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
        fw.add(i, 1);
        w[p[i]] = i;
    }
    auto find_cycles = [&]() ->vector<vector<int> >  {
        vector<vector<int> > cycles;
        vector<int> used(n);
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                int cur = i;
                vector<int> v;
                while(!used[cur]) {
                    v.push_back(cur);
                    used[cur] = 1;
                    cur = p[cur];
                }
                if (v.size() > 1)
                    cycles.push_back(v);
            }
        }
        return cycles;
    };
    auto v = find_cycles();
 
    vector<ll> res(4);
    for (int i = 0; i < n; ++i) {
        res[0] += fw.sum(0, w[i]);
        fw.add(w[i], -1);
    }
    for (auto x : v) {
        res[1] += (int)x.size() - 1;
    }
    res[2] = n - calc_lis(p).size();
 
    res[3] = n - 1;
    while(res[3] && w[res[3]] > w[res[3] - 1])
        --res[3];
    cout << res[0] << ' ' << res[1] << ' ' << res[2] << ' ' << res[3] << '\n';

    return 0;
}
