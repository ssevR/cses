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
#include <utility>
#include <vector>
 
namespace atcoder {
namespace internal {
 
template <class E> struct csr {
    std::vector<int> start;
    std::vector<E> elist;
    explicit csr(int n, const std::vector<std::pair<int, E>>& edges)
        : start(n + 1), elist(edges.size()) {
        for (auto e : edges) {
            start[e.first + 1]++;
        }
        for (int i = 1; i <= n; i++) {
            start[i] += start[i - 1];
        }
        auto counter = start;
        for (auto e : edges) {
            elist[counter[e.first]++] = e.second;
        }
    }
};
 
}  // namespace internal
 
}  // namespace atcoder
 
 
namespace atcoder {
namespace internal {
 
struct scc_graph {
  public:
    explicit scc_graph(int n) : _n(n) {}
 
    int num_vertices() { return _n; }
 
    void add_edge(int from, int to) { edges.push_back({from, {to}}); }
 
    std::pair<int, std::vector<int>> scc_ids() {
        auto g = csr<edge>(_n, edges);
        int now_ord = 0, group_num = 0;
        std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
        visited.reserve(_n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = ord[v] = now_ord++;
            visited.push_back(v);
            for (int i = g.start[v]; i < g.start[v + 1]; i++) {
                auto to = g.elist[i].to;
                if (ord[to] == -1) {
                    self(self, to);
                    low[v] = std::min(low[v], low[to]);
                } else {
                    low[v] = std::min(low[v], ord[to]);
                }
            }
            if (low[v] == ord[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    ord[u] = _n;
                    ids[u] = group_num;
                    if (u == v) break;
                }
                group_num++;
            }
        };
        for (int i = 0; i < _n; i++) {
            if (ord[i] == -1) dfs(dfs, i);
        }
        for (auto& x : ids) {
            x = group_num - 1 - x;
        }
        return {group_num, ids};
    }
 
    std::vector<std::vector<int>> scc() {
        auto ids = scc_ids();
        int group_num = ids.first;
        std::vector<int> counts(group_num);
        for (auto x : ids.second) counts[x]++;
        std::vector<std::vector<int>> groups(ids.first);
        for (int i = 0; i < group_num; i++) {
            groups[i].reserve(counts[i]);
        }
        for (int i = 0; i < _n; i++) {
            groups[ids.second[i]].push_back(i);
        }
        return groups;
    }
 
  private:
    int _n;
    struct edge {
        int to;
    };
    std::vector<std::pair<int, edge>> edges;
};
 
}  // namespace internal
 
}  // namespace atcoder
 
 
namespace atcoder {
 
struct scc_graph {
  public:
    scc_graph() : internal(0) {}
    explicit scc_graph(int n) : internal(n) {}
 
    void add_edge(int from, int to) {
        int n = internal.num_vertices();
        assert(0 <= from && from < n);
        assert(0 <= to && to < n);
        internal.add_edge(from, to);
    }
 
    std::vector<std::vector<int>> scc() { return internal.scc(); }
 
  private:
    internal::scc_graph internal;
};
 
}  // namespace atcoder
 
using namespace atcoder;
 
// https://atcoder.github.io/ac-library/production/document_en/scc.html
/*
scc_graph graph(int n)
void graph.add_edge(int from, int to)
vector<vector<int>> graph.scc()
*/
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
 
// if the graph is not DAG, return empty vector
vector<int> top_sort(const vector<vector<int> >& g) {
    int n = (int)g.size();
    vector<int> used(n, 0), is_parent(n, 0), res;
    auto dfs = [&](int v, auto&& dfs) -> bool {
        if (is_parent[v] == 1) return false;
        if (!used[v]) {
            used[v] = 1;
            is_parent[v] = 1;
            for (auto u : g[v]) {
                if (!dfs(u, dfs)) return false;
            }
            res.push_back(v);
            is_parent[v] = 0;
        }
        return true;
    };
 
    for (int v = 0; v < n; v++) {
        if (used[v] == 0) {
            if (dfs(v, dfs) == false) return vector<int>();
        }
    }
    reverse(res.begin(), res.end());
    return res;
}
 
int main() {
    IOS;
 
    int n, m;
    cin >> n >> m;
    scc_graph g(n);
    vector<vector<int> > g_o(n);
    vector<int> k(n);
    for (int i = 0; i < n; ++i)
        cin >> k[i];
 
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g.add_edge(v, u);
        g_o[v].push_back(u);
    }
 
    auto s = g.scc();
 
 
    vector<int> w(n);
 
    vector<ll> s_k(s.size());
    vector<ll> dp(s.size());
 
    for (int i = 0; i < s.size(); ++i) {
        for (auto v : s[i]) {
            w[v] = i;
            s_k[i] += k[v];
        }
    }
    
    ll res = 0;
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        dp[i] = s_k[i];
        for (auto v : s[i]) {
            for (auto u : g_o[v]) {
                if (w[v] != w[u]) {
                    dp[i] = max(dp[i], s_k[i] + dp[w[u]]);
                }
            }
        }
 
        res = max(res, dp[i]);
    }
    cout << res << '\n';
 
}
