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
    int val;
    int min;
    bool rev;
    pitem l, r;
};
 
int cnt(pitem it) {
    return it ? it->cnt : 0;
}
 
void upd_cnt(pitem it) {
    if (it) {
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
        it->min = it->val;
        if (it->l)
            it->min = min(it->min, it->l->min);
        if (it->r)
            it->min = min(it->min, it->r->min);
    }
}
 
void push (pitem it) {
	if (it && it->rev) {
		it->rev = false;
		swap (it->l, it->r);
		if (it->l)  it->l->rev ^= true;
		if (it->r)  it->r->rev ^= true;
	}
}
 
void merge(pitem& t, pitem l, pitem r) {
    push(l);
    push(r);
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
    push(t);
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
 
void reverse_treap (pitem t, int l, int r) {
	pitem t1, t2, t3;
	split (t, t1, t2, l);
	split (t2, t2, t3, r-l+1);
	t2->rev ^= true;
	merge (t, t1, t2);
	merge (t, t, t3);
}
 
int find(pitem t) {
    push(t);
    if (t->min == t->val)
        return cnt(t->l);
 
    if (t->l && t->min == t->l->min) {
        return find(t->l);
    }
    else {
        return cnt(t->l) + 1 + find(t->r);
    }
}
 
void output (pitem t) {
	if (!t)  return;
    push(t);
	output (t->l);
    cout << t->val << ' ';
	output (t->r);
}
 
 
int main() {
    IOS;
    int n;
    cin >> n;
    vector<pitem> dr(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        dr[i] = new item{rnd(), 1, x, x, false, NULL, NULL};
    }
    pitem root = dr[0];
    for (int i = 1; i < n; ++i) {
        merge(root, root, dr[i]);
    }
    cout << n - 1 << '\n';
    for (int i = 0; i < n - 1; ++i) {
        int ind = find(root);
        cout << i + 1 << ' ' << i + ind + 1 << endl;
        reverse_treap(root, 0, ind);
        pitem tmp;
        split(root, tmp, root, 1);
    }
 
 
    for (int i = 0; i < n; ++i)
        delete dr[i];

    return 0;
}
