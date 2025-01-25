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
 
struct Node {
    ll sum = 0;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};
 
shared_ptr<Node> build(vector<int>& v, int l, int r) {
    shared_ptr<Node> cur(new Node);
    if (l + 1 == r) {
        cur.get()->sum = v[l];
        return cur;
    }
    int mid = (r + l) / 2;
    if (l < mid) {
        cur.get()->left = shared_ptr<Node>(build(v, l, mid));
        cur.get()->sum += cur.get()->left.get()->sum;
    }
    if (mid < r) {
        cur.get()->right = shared_ptr<Node>(build(v, mid, r));
        cur.get()->sum += cur.get()->right.get()->sum;
    }
    return cur;
}
 
shared_ptr<Node> update(shared_ptr<Node> cur, int i, int lx, int rx, int x) {
    if (lx + 1 == rx) {
        cur.get()->sum = x;
        return cur;
    }
    int mx = (lx + rx) / 2;
    if (i < mx) {
        auto old = *(cur.get()->left.get());
        cur.get()->sum -= old.sum;
        cur.get()->left = shared_ptr<Node>(new Node(old));
 
        update(cur.get()->left, i, lx, mx, x);
        cur.get()->sum += cur.get()->left.get()->sum;
    }
    else {
        auto old = *(cur.get()->right.get());
        cur.get()->sum -= old.sum;
        cur.get()->right = shared_ptr<Node>(new Node(old));
 
        update(cur.get()->right, i, mx, rx, x);
        cur.get()->sum += cur.get()->right.get()->sum;
    }
    return cur;
}
 
 
ll find_sum(shared_ptr<Node> root, int l, int r, int lx, int rx) {
    int L = max(l, lx);
    int R = min(r, rx);
    if (L >= R)
        return 0;
    if (l <= lx && rx <= r) {
        return root.get()->sum;
    }
    int mx = (lx + rx) / 2;
    return find_sum(root.get()->left, l, r, lx, mx) + find_sum(root.get()->right, l, r, mx, rx);
}
 
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    vector<shared_ptr<Node> > roots;
    roots.reserve(100000);
    roots.push_back(build(v, 0, n));
    while(q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, a, x;
            cin >> k >> a >> x;
            --k, --a;
            update(roots[k], a, 0, n, x);
        }
        else if (t == 2) {
            int k, a, b;
            cin >> k >> a >> b;
            --k, --a;
            cout << find_sum(roots[k], a, b, 0, n) << '\n';
        }
        else {
            int k;
            cin >> k;
            --k;
            roots.push_back(shared_ptr<Node>(new Node(*roots[k].get())));
        }
    }
}
