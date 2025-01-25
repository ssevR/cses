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
 
int rnd() {
    static int x = 0;
    return (x = (x * 1103515245 + 12345) & 0x7FFFFFFF);
}
 
//http://e-maxx.ru/algo/treap
 
typedef struct item * pitem;
 
struct item {
    int prior, cnt;
    char c;
    pitem l, r;
};
 
int cnt(pitem it) {
    return it ? it->cnt : 0;
}
 
void upd_cnt(pitem it) {
    if (it) it->cnt = cnt(it->l) + cnt(it->r) + 1;
}
 
void merge(pitem& t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior) {
        merge(l->r, l->r, r);
        t = l;
    }
    else {
        merge (r->l, l, r->l);  
        t = r;
    }
    upd_cnt(t);
}
 
void split(pitem t, pitem&l, pitem&r, int key, int add = 0) {
    if (!t) {
        l = NULL;
        r = NULL;
        return;
    }
    int cur = add + cnt(t->l);
    if (key <= cur) {
        split (t->l, l, t->l, key, add);  
        r = t;
    }
    else {
        split (t->r, t->r, r, key, add + 1 + cnt(t->l));  
        l = t;
    }
    upd_cnt(t);
}
 
void output (pitem t) {
	if (!t)  return;
	output (t->l);
    cout << t->c;
	output (t->r);
}
 
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<pitem> dr(n);
    string s;
    cin >> s;
    for (int i = 0; i < n; ++i) {
        dr[i] = new item{rnd(), 1, s[i], NULL, NULL};
    }
    pitem root = dr[0];
    for (int i = 1; i < n; ++i) {
        merge(root, root, dr[i]);
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        --l;
        pitem f1, f2, f3;
        split(root, f1, f2, l);
        split(f2, f2, f3, r - l);
        merge(f1, f1, f3);
        merge(root, f1, f2);
    }
    output(root);
    cout << '\n';
    for (int i = 0; i < n; ++i)
        delete dr[i];
}
