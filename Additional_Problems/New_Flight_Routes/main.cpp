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
 
 
#include <utility>
 
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
 
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    scc_graph g(n);
    vector<vector<int> > gr(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g.add_edge(v, u);
        gr[v].push_back(u);
    }
    auto sc = g.scc();
    if (sc.size() == 1) {
        cout << 0 << '\n';
        return 0;
    }
 
    vector<int> color(n);
    vector<set<int> > gs(sc.size());
    for (int i = 0; i < sc.size(); ++i) {
        for (auto v : sc[i])
            color[v] = i;
    }
 
    for (int v = 0; v < n; ++v) 
        for (auto u : gr[v])
            if (color[v] != color[u]) {
                gs[color[v]].insert(color[u]);
            }
    vector<int> in(gs.size()), out(gs.size());
    for (int v = 0; v < gs.size(); ++v) 
        for (auto u : gs[v]) {
            ++out[v];
            ++in[u];
        }
 
    //int res = max(count(in.begin(), in.end(), 0), count(out.begin(), out.end(), 0));
    //cout << res << '\n';
 
    vector<int> used(gs.size());
 
    vector<int> parent(gs.size());
    vector<int> son(gs.size());
 
    
    for (int i = 0; i < gs.size(); ++i) {
        auto dfs = [&](int v, auto&& dfs) -> void {
            used[v] = 1;
            parent[v] = i;
 
            if (gs[v].size() == 0) {
                son[v] = v;
            }
            for (auto u : gs[v]) {
                if (!used[u]) {
                    dfs(u, dfs);
                }
                son[v] = son[u];
            }
        };
        if (!used[i] && in[i] == 0) {
            dfs(i, dfs);
        }
    }
 
    fill(used.begin(), used.end(), 0);
    vector<pii> f;
    for (int i = 0; i < gs.size(); ++i) {
        if (in[i] == 0 && !used[i] && !used[son[i]]) {
            f.emplace_back(i, son[i]);
            used[i] = used[son[i]] = 1;
        }
        else if (out[i] == 0 && !used[i] && !used[parent[i]]) {
            f.emplace_back(parent[i], i);
            used[parent[i]] = used[i] = 1;
        }
    }
    /*for (auto x : f) {
        cout << sc[x.fi].front() + 1 << ' ' << sc[x.se].front() + 1 << '\n';
    }*/
 
    vector<pii> res;
    for (int i = 0; i < f.size(); ++i) {
        res.emplace_back(sc[f[i].se].front(), sc[f[(i + 1) % f.size()].fi].front());
        used[f[i].fi] = used[f[(i + 1) % f.size()].se] = 1;
    }
    vector<int> IN, OUT;
    for (int i = 0; i < gs.size(); ++i) {
        if (in[i] == 0 && !used[i]) {
            IN.push_back(i);
            used[i] = 1;
        }
        if (out[i] == 0 && !used[i]) {
            OUT.push_back(i);
        }
    }
    if (!IN.empty() || !OUT.empty()) {
        if (IN.empty()) {
            IN.push_back(f[0].fi);
        }
        if (OUT.empty()) {
            OUT.push_back(f[0].se);
        }
        for (int i = 0; i < max(IN.size(), OUT.size()); ++i) {
            int v = IN[i % IN.size()];
            int u = OUT[i % OUT.size()];
            res.emplace_back(sc[u].front(), sc[v].front());
        }
    }
    cout << res.size() << '\n';
    for (auto [v, u]: res) {
        cout << v + 1 << ' ' << u + 1 << '\n';
    }

    return 0;
}
