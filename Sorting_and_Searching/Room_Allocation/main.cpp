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
 
int main() {
    IOS;
    int n;
    cin >> n;
    set<int> rooms;
    vector<pair<pii, int> > lin;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        lin.emplace_back(mp(a, 0), i);
        lin.emplace_back(mp(b, 1), i);
    }
 
 
    vector<int> res(n);
    vector<int> used(n);
 
    sort(lin.begin(), lin.end());
    int cnt = 0;
    for (auto cur: lin) {
        int x = cur.fi.fi;
        int ind = cur.se;
        if (!used[ind]) {
            used[ind] = 1;
            if (rooms.empty()) {
                rooms.insert(cnt);
                ++cnt;
            }
            res[ind] = *rooms.begin();
            rooms.erase(rooms.begin());
        }
        else {
            rooms.insert(res[ind]);
        }
    }
    cout << cnt << '\n';
    for (int i = 0; i < n; ++i)
        cout << res[i] + 1 << ' ';
    cout << '\n';
}
