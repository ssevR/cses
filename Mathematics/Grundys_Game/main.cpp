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
 
 
const int N = 1222;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    IOS;
    vector<int> gr(N + 1);
    gr[1] = 0;
    gr[2] = 0;
    for (int i = 3; i <= N; ++i) {
        vector<int> f;
        for (int j = 1; j * 2 < i; ++j) {
            f.push_back(gr[j] ^ gr[i - j]);
        }
        sort(f.begin(), f.end());
        int cur = 0;
        for (auto x : f)
            if (x == cur)
                ++cur;
        gr[i] = cur;
    }
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        if (n > N || gr[n] > 0)
            cout << "first\n";
        else
            cout << "second\n";
    }
}
