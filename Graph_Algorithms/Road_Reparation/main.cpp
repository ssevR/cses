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
#include <vector>
 
namespace atcoder {
 
struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}
 
    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }
 
    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }
 
    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }
 
    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }
 
    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }
 
  private:
    int _n;
    std::vector<int> parent_or_size;
};
 
}  // namespace atcoder
 
 
//https://atcoder.github.io/ac-library/production/document_en/dsu.html
/*
dsu d(int n)
int d.merge(int a, int b)
bool d.same(int a, int b)
int d.leader(int a)
int d.size(int a)
vector<vector<int>> d.groups()
*/
 
using namespace atcoder;
 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    int n, m;
    cin >> n >> m;
    dsu d(n);
    vector<pair<int, pii> > edges;
 
    for (int i = 0; i < m; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        edges.emplace_back(w, mp(v, u));
 
 
    }
    sort(edges.begin(), edges.end());
 
    ll res = 0;
    int cnt = n;
    for (auto x : edges) {
        int w = x.fi;
        auto [v, u] = x.se;
        if (d.same(v, u))
            continue;
        else {
            d.merge(v, u);
            res += w;
            --cnt;
        }
    }
    if (cnt == 1) {
        cout << res << '\n';
    }
    else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
