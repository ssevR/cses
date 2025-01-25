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
};
 
int main() {
    IOS;
    int n;
    cin >> n;
    vector<P> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].read();
    }

    long long boundary = 0;
    long long area = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        auto diff = p[j] - p[i];
        boundary += abs(__gcd(diff.x, diff.y));
        area += p[i] * p[j];
    }
    area = abs(area);

    cout << (area - boundary + 2) / 2 << ' ' << boundary << '\n';
}
