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

    P operator-(const P& b) {
        return P{x - b.x, y - b.y};
    }
    void operator-=(const P& b) {
        x -= b.x;
        y -= b.y;
    }

    long long operator* (const P& b) {
        return x * b.y - y * b.x;
    }
};



const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    IOS;

    int t;
    cin >> t;
    while(t--) {
        P p[3];
        for (int i = 0; i < 3; ++i) {
            p[i].read();
            if (i > 0) {
                p[i] -= p[0];
            }
        }
        auto sc = p[1] * p[2];
        if (sc < 0)
            cout << "RIGHT\n";
        else if (sc == 0)
            cout << "TOUCH\n";
        else 
            cout << "LEFT\n";
    }
}
