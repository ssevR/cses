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


struct P {
    long long x, y;
 
    void read() {
        cin >> x >> y;
    }
 
    P operator-(const P& b) const {
        return P{x - b.x, y - b.y};
    }
    void operator-=(const P& b) {
        x -= b.x;
        y -= b.y;
    }
 
    long long operator* (const P& b) {
        return x * b.y - y * b.x;
    }
    long long triangle(const P& b, const P& c) const{
        return (b - *this) * (c - *this);
    }
    bool is_in_segment(const P& b, const P& c) const {
        if ((*this).triangle(b, c))
            return 0;
        if (max(b.x, c.x) < x || max(b.y, c.y) < y ||
                min(b.x, c.x) > x || min(b.y, c.y) > y)
            return 0;
        return 1;

    }
};


int is_intersect(P p1, P p2, P p3, P p4) {
    for (int i = 0; i < 2; ++i) {
        auto sign1 = (p2 - p1) * (p3 - p1);
        auto sign2 = (p2 - p1) * (p4 - p1);
        if ((sign1 > 0 && sign2 > 0) || (sign1 < 0 && sign2 < 0)) {
            return 0;
        }
        swap(p1, p3);
        swap(p2, p4);
    }
    if ((p2 - p1) * (p4 - p3) == 0) {
        for (int i = 0; i < 2; ++i) {
            if ((max(p1.x, p2.x) < min(p3.x, p4.x)) || (max(p1.y, p2.y) < min(p3.y, p4.y))) {
                return 0;
            }
            swap(p1, p3);
            swap(p2, p4);
        }
    }
    return 1;
}

int is_in_segment(P a, P b, P c) {
    if (c.triangle(a, b))
        return 0;
    if (max(a.x, b.x) < c.x || max(a.y, b.y) < c.y ||
        min(a.x, b.x) > c.x || min(a.y, b.y) > c.y)
        return 0;
    return 1;
}


 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<P> p(n);
    for (int i = 0; i < n; ++i)
        p[i].read();

    while(m--) {
        P f[2];
        f[0].read();

        f[1].x = f[0].x + 1;
        f[1].y = 3ll * INF;

        int cnt = 0;
        int flag = 0;
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            if (f[0].is_in_segment(p[i], p[j])) {
                flag = 1;
                break;
            }
            if (is_intersect(f[0], f[1], p[i], p[j]))
                ++cnt;
        }
        if (flag) {
            cout << "BOUNDARY\n";
        }
        else if (cnt % 2)
            cout << "INSIDE\n";
        else
            cout << "OUTSIDE\n";
    }
}
