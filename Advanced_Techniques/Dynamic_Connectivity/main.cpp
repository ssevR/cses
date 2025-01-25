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
 
 
const int N = 3e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int cnt = 0;
 
int dsuP[N], dsuR[N];
vector < pair < int*, pair<int, int> > > hist;
 
int dsuRoot(int v)
{
    while (dsuP[v] != -1)
        v = dsuP[v];
    return v;
}
 
void dsuMerge(int a, int b) {
    a = dsuRoot(a);
    b = dsuRoot(b);
    if (a == b)
        return;
    --cnt;
    if (dsuR[a] > dsuR[b]) {
        hist.emplace_back(&dsuP[b], make_pair(dsuP[b], 1));
        dsuP[b] = a;
    } else if (dsuR[a] < dsuR[b]) {
        hist.emplace_back(&dsuP[a], make_pair(dsuP[a], 1));
        dsuP[a] = b;
    } else {
        hist.emplace_back(&dsuP[a], make_pair(dsuP[a], 1));
        hist.emplace_back(&dsuR[b], make_pair(dsuR[b], 0));
        dsuP[a] = b;
        ++dsuR[b];
    }
}
 
struct Query {
    int t, u, v;
    int answer;
};

int n, m, k;
Query q[N];
 
vector <pii> t[N*4];
 
void addEdge(int l, int r, pii uv, int c, int cl, int cr) {
    if (l > cr || r < cl)
        return;
    if (l <= cl && cr <= r) {
        t[c].push_back(uv);
        return;
    }
    int mid = (cl + cr) / 2;
    addEdge(l, r, uv, c * 2 + 1, cl, mid);
    addEdge(l, r, uv, c * 2 + 2, mid + 1, cr);
}
 
void go(int c, int cl, int cr) {
    if (cl > cr)
        return;
 
    int startSize = hist.size();

    for (pii uv : t[c])
        dsuMerge(uv.first, uv.second);

    if (cl == cr) {
        if (q[cl].t == 3)
            q[cl].answer = cnt;
    } else {
        int mid = (cl + cr) / 2;
        go(c*2+1, cl, mid);
        go(c*2+2, mid+1, cr);
    }
 
    while ((int)hist.size() > startSize)
    {
        cnt += hist.back().second.second;
        *hist.back().first = hist.back().second.first;
        hist.pop_back();
    }
}
 
int main() {
    IOS;

    cin >> n >> m >> k;
    cnt = n;
    for (int i = 0; i < n; ++i)
        dsuP[i] = -1;
    
    set < pair < pii, int > > edges;
    for (int ind = 0, i = 0; ind < m + k; ++ind) {
        if (ind < m) {
            q[i].t = 1;
        }
        else {
            cin >> q[i].t;
        }
        cin >> q[i].v >> q[i].u;
        --q[i].v, --q[i].u;

        if (q[i].u > q[i].v) swap(q[i].u, q[i].v);
        if (q[i].t == 1) {
            edges.emplace(pii(q[i].u, q[i].v), i);
        }
        else if (q[i].t == 2) {
            auto iter = edges.lower_bound(make_pair(pii(q[i].u, q[i].v), 0));
            addEdge(iter->second, i, iter->first, 0, 0, N - 1);
            edges.erase(iter);
        }
        if (ind >= m - 1) {
            ++i;
            q[i].t = 3;
        }
        ++i;
    }

    for (auto e : edges)
        addEdge(e.second, N - 1, e.first, 0, 0, N - 1);
    
    go(0, 0, N - 1);

    for (int i = 0; i < N; ++i)
        if (q[i].t == 3)
            cout << q[i].answer << ' ';
    cout << '\n';
 
    return 0;
}
