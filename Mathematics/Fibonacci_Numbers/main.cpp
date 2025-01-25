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
#include <numeric>
#include <type_traits>
 
#ifdef _MSC_VER
#include <intrin.h>
#endif
 
 
#include <utility>
 
#ifdef _MSC_VER
#include <intrin.h>
#endif
 
namespace atcoder {
 
namespace internal {
 
constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}
 
struct barrett {
    unsigned int _m;
    unsigned long long im;
 
    explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}
 
    unsigned int umod() const { return _m; }
 
    unsigned int mul(unsigned int a, unsigned int b) const {
 
        unsigned long long z = a;
        z *= b;
#ifdef _MSC_VER
        unsigned long long x;
        _umul128(z, im, &x);
#else
        unsigned long long x =
            (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
        unsigned long long y = x * _m;
        return (unsigned int)(z - y + (z < y ? _m : 0));
    }
};
 
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    unsigned long long r = 1;
    unsigned long long y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}
 
constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr long long bases[3] = {2, 7, 61};
    for (long long a : bases) {
        long long t = d;
        long long y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);
 
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
 
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;
 
    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b
 
 
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
 
constexpr int primitive_root_constexpr(int m) {
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int i = 3; (long long)(i)*i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        divs[cnt++] = x;
    }
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt; i++) {
            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
template <int m> constexpr int primitive_root = primitive_root_constexpr(m);
 
unsigned long long floor_sum_unsigned(unsigned long long n,
                                      unsigned long long m,
                                      unsigned long long a,
                                      unsigned long long b) {
    unsigned long long ans = 0;
    while (true) {
        if (a >= m) {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }
 
        unsigned long long y_max = a * n + b;
        if (y_max < m) break;
        n = (unsigned long long)(y_max / m);
        b = (unsigned long long)(y_max % m);
        std::swap(m, a);
    }
    return ans;
}
 
}  // namespace internal
 
}  // namespace atcoder
 
 
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
 
namespace internal {
 
struct modint_base {};
struct static_modint_base : modint_base {};
 
template <class T> using is_modint = std::is_base_of<modint_base, T>;
template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;
 
}  // namespace internal
 
template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
struct static_modint : internal::static_modint_base {
    using mint = static_modint;
 
  public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }
 
    static_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    static_modint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    static_modint(T v) {
        _v = (unsigned int)(v % umod());
    }
 
    unsigned int val() const { return _v; }
 
    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }
 
    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
 
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
 
    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        if (prime) {
            assert(_v);
            return pow(umod() - 2);
        } else {
            auto eg = internal::inv_gcd(_v, m);
            assert(eg.first == 1);
            return eg.second;
        }
    }
 
    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }
 
  private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
    static constexpr bool prime = internal::is_prime<m>;
};
 
template <int id> struct dynamic_modint : internal::modint_base {
    using mint = dynamic_modint;
 
  public:
    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) {
        assert(1 <= m);
        bt = internal::barrett(m);
    }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }
 
    dynamic_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        long long x = (long long)(v % (long long)(mod()));
        if (x < 0) x += mod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        _v = (unsigned int)(v % mod());
    }
 
    unsigned int val() const { return _v; }
 
    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }
 
    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v += mod() - rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        _v = bt.mul(_v, rhs._v);
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
 
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
 
    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        auto eg = internal::inv_gcd(_v, mod());
        assert(eg.first == 1);
        return eg.second;
    }
 
    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }
 
  private:
    unsigned int _v;
    static internal::barrett bt;
    static unsigned int umod() { return bt.umod(); }
};
template <int id> internal::barrett dynamic_modint<id>::bt(998244353);
 
using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;
 
namespace internal {
 
template <class T>
using is_static_modint = std::is_base_of<internal::static_modint_base, T>;
 
template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;
 
template <class> struct is_dynamic_modint : public std::false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};
 
template <class T>
using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;
 
}  // namespace internal
 
}  // namespace atcoder
 
 
using namespace atcoder;
 
//using mint = modint998244353;
//const int MOD = 998244353;
using mint = modint1000000007;
const int MOD = 1e9 + 7;
 
 
 
template <typename T>
std::pair<int, T> GaussElimination(vector<vector<T>> &a, int pivot_end = -1,
        bool diagonalize = false) {
    if (a.empty()) return {0, 1};
    int H = a.size(), W = a[0].size(), rank = 0;
    if (pivot_end == -1) pivot_end = W;
    T det = 1;
    for (int j = 0; j < pivot_end; j++) {
        int idx = -1;
        for (int i = rank; i < H; i++) {
            if (a[i][j] != T(0)) {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            det = 0;
            continue;
        }
        if (rank != idx) det = -det, swap(a[rank], a[idx]);
        det *= a[rank][j];
        if (diagonalize && a[rank][j] != T(1)) {
            T coeff = T(1) / a[rank][j];
            for (int k = j; k < W; k++) a[rank][k] *= coeff;
        }
        int is = diagonalize ? 0 : rank + 1;
        for (int i = is; i < H; i++) {
            if (i == rank) continue;
            if (a[i][j] != T(0)) {
                T coeff = a[i][j] / a[rank][j];
                for (int k = j; k < W; k++) a[i][k] -= a[rank][k] * coeff;
            }
        }
        rank++;
    }
    return make_pair(rank, det);
}
 
template <typename mint>
vector<vector<mint>> inverse_matrix(const vector<vector<mint>>& a) {
    int N = a.size();
    assert(N > 0);
    assert(N == (int)a[0].size());
 
    vector<vector<mint>> m(N, vector<mint>(2 * N));
    for (int i = 0; i < N; i++) {
        copy(begin(a[i]), end(a[i]), begin(m[i]));
        m[i][N + i] = 1;
    }
 
    auto [rank, det] = GaussElimination(m, N, true);
    if (rank != N) return {};
 
    vector<vector<mint>> b(N);
    for (int i = 0; i < N; i++) {
        copy(begin(m[i]) + N, end(m[i]), back_inserter(b[i]));
    }
    return b;
}
 
template <class T>
struct Matrix {
    vector<vector<T> > A;
 
    Matrix() = default;
    Matrix(int n, int m) : A(n, vector<T>(m, T())) {}
    Matrix(int n) : A(n, vector<T>(n, T())){};
 
    int H() const { return A.size(); }
 
    int W() const { return A[0].size(); }
 
    int size() const { return A.size(); }
 
    inline const vector<T> &operator[](int k) const { return A[k]; }
 
    inline vector<T> &operator[](int k) { return A[k]; }
 
    static Matrix I(int n) {
        Matrix mat(n);
        for (int i = 0; i < n; i++) mat[i][i] = 1;
        return (mat);
    }
 
    Matrix &operator+=(const Matrix &B) {
        int n = H(), m = W();
        assert(n == B.H() && m == B.W());
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
        return (*this);
    }
 
    Matrix &operator-=(const Matrix &B) {
        int n = H(), m = W();
        assert(n == B.H() && m == B.W());
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
        return (*this);
    }
 
    Matrix &operator*=(const Matrix &B) {
        int n = H(), m = B.W(), p = W();
        assert(p == B.H());
        vector<vector<T> > C(n, vector<T>(m, T{}));
        for (int i = 0; i < n; i++)
            for (int k = 0; k < p; k++)
                for (int j = 0; j < m; j++) C[i][j] += (*this)[i][k] * B[k][j];
        A.swap(C);
        return (*this);
    }
 
    Matrix &operator^=(long long k) {
        Matrix B = Matrix::I(H());
        while (k > 0) {
            if (k & 1) B *= *this;
            *this *= *this;
            k >>= 1LL;
        }
        A.swap(B.A);
        return (*this);
    }
 
    Matrix operator+(const Matrix &B) const { return (Matrix(*this) += B); }
 
    Matrix operator-(const Matrix &B) const { return (Matrix(*this) -= B); }
 
    Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }
 
    Matrix operator^(const long long k) const { return (Matrix(*this) ^= k); }
 
    bool operator==(const Matrix &B) const {
        assert(H() == B.H() && W() == B.W());
        for (int i = 0; i < H(); i++)
            for (int j = 0; j < W(); j++)
                if (A[i][j] != B[i][j]) return false;
        return true;
    }
 
    bool operator!=(const Matrix &B) const {
        assert(H() == B.H() && W() == B.W());
        for (int i = 0; i < H(); i++)
            for (int j = 0; j < W(); j++)
                if (A[i][j] != B[i][j]) return true;
        return false;
    }
 
    Matrix inverse() const {
        assert(H() == W());
        Matrix B(H());
        B.A = inverse_matrix(A);
        return B;
    }
 
    friend ostream &operator<<(ostream &os, const Matrix &p) {
        int n = p.H(), m = p.W();
        for (int i = 0; i < n; i++) {
            os << (i ? "   " : "") << "[";
            for (int j = 0; j < m; j++) {
                os << p[i][j] << (j + 1 == m ? "]\n" : ",");
            }
        }
        return (os);
    }
 
    T determinant() const {
        Matrix B(*this);
        assert(H() == W());
        T ret = 1;
        for (int i = 0; i < H(); i++) {
            int idx = -1;
            for (int j = i; j < W(); j++) {
                if (B[j][i] != 0) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) return 0;
            if (i != idx) {
                ret *= T(-1);
                swap(B[i], B[idx]);
            }
            ret *= B[i][i];
            T inv = T(1) / B[i][i];
            for (int j = 0; j < W(); j++) {
                B[i][j] *= inv;
            }
            for (int j = i + 1; j < H(); j++) {
                T a = B[j][i];
                if (a == 0) continue;
                for (int k = i; k < W(); k++) {
                    B[j][k] -= B[i][k] * a;
                }
            }
        }
        return ret;
    }
};
 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    Matrix<mint> M(2, 2);
    M[0][0] = M[0][1] = M[1][0] = 1;
    ll n;
    cin >> n;
    M ^= n;
    cout << M[0][1].val() << '\n';

    return 0;
}
