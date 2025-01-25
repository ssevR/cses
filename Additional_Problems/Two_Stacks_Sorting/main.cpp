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
 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int parent[N];
int len[N];
 
struct cmp{
    bool operator() (const pii& a, const pii& b) const {
        if (a.se != b.se)
            return a.se < b.se;
        else
            return a.fi < b.fi;
    }
};
 
set<pii, cmp> lr[N];
 
pii find_set(int v) {
    if (v == parent[v]) return mp(v, 0);
    auto tmp = find_set(parent[v]);
    parent[v] = tmp.fi;
    len[v] = (len[v] + tmp.se) % 2;
 
    return mp(parent[v], len[v]);
 
}
 
int union_sets(int v, int u) {
    auto tmp1 = find_set(v);
    auto tmp2 = find_set(u);
    if (tmp1.fi != tmp2.fi) {
        parent[tmp1.fi] = tmp2.fi;
        len[tmp1.fi] = (1 + tmp1.se + tmp2.se) % 2;
        if (lr[tmp2.fi].size() < lr[tmp1.fi].size())
            swap(lr[tmp2.fi], lr[tmp1.fi]);
        lr[tmp2.fi].insert(lr[tmp1.fi].begin(), lr[tmp1.fi].end());
        return 1;
    }
    else if (tmp1 == tmp2) {
        return 0;
    }
    else {
        return 1;
    }
}
 
 
int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(n);
    vector<pii> f(n);
    vector<int> w(n);
    vector<int> used(n + 1);
    iota(parent, parent + n, 0);
 
 
    int tim = 0;
    for (int i = 0, cur = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        w[a[i]] = i;
        used[a[i]] = 1;
 
        f[i].fi = tim++;
        while(used[cur]) {
            f[w[cur]].se = tim++;
            ++cur;
        }
    }
    vector<pii> l(tim, mp(-1, -1));
    for (int i = 0; i < n; ++i) {
        l[f[i].fi] = {i, 0};
        l[f[i].se] = {i, 1};
        lr[i].insert(mp(f[i].fi, f[i].se));
    }
    set<pii> s; // en, ind
    for (int i = 0; i < tim; ++i) {
        if (l[i].se == -1) continue;
        int ind = l[i].fi;
 
        if (l[i].se == 0) {
            int mi_en = f[ind].se;
            int mi_ind = ind;
 
            for (auto [en, set_ind] : s) {
                if (en > f[ind].se)
                    break;
                if (en < mi_en) {
                    mi_en = en;
                    mi_ind = set_ind;
                }
                if (!union_sets(set_ind, ind)) {
                    cout << "IMPOSSIBLE\n";
                    return 0;
                }
            }
            while(!s.empty() && (*s.begin()).fi <= f[ind].se) {
                s.erase(s.begin());
            }
            s.insert(mp(mi_en, mi_ind));
        }
        else {
            int p = find_set(ind).fi;
            if (!s.count(mp(f[ind].se, ind))) {
                continue;
            }
            s.erase(mp(f[ind].se, ind));
            auto it = lr[p].lower_bound({-1, f[ind].se + 1});
            if (it != lr[p].end()) {
                s.insert(mp(it->se, l[it->se].fi));
            }
        }
    }
 
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = find_set(i).se;
    }
    stack<int> b[2];
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (!b[res[i]].empty() && b[res[i]].top() < a[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        b[res[i]].push(a[i]);
        while(true) {
            if (!b[0].empty() && b[0].top() == cur) 
                b[0].pop(), ++cur;
            else if (!b[1].empty() && b[1].top() == cur)
                b[1].pop(), ++cur;
            else
                break;
        }
    }
    if (cur != n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < n; ++i)
        cout << res[i] + 1 << ' ';
    cout << '\n';

    return 0;
}
