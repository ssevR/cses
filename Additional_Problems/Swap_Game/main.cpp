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
 
 
int v[362880][10];
int deg[9];
 
int main() {
    deg[0] = 1;
    for (int i = 1; i < 9; ++i) {
        deg[i] = deg[i - 1] * 10;
    }
    unordered_set<int> s;
    s.insert(876543210);
 
    for (int i = 0; i < 9; ++i)
        v[0][i] = i;
    v[0][9] = 0;
 
    int sz = 1;
 
    int a[9];
    for (int i = 0; i < 9; ++i) {
        cin >> a[i];
        --a[i];
    }
 
    for (int z = 0; z < 362880; ++z) {
        if (memcmp(a, v[z], sizeof(a)) == 0) {
            cout << v[z][9] << '\n';
            return 0;
        }
 
        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 2; ++j) {
                swap(v[z][i + j], v[z][i + j + 1]);
 
                int h = 0;
                for (int y = 0; y < 9; ++y)
                    h += deg[y] * v[z][y];
                if (!s.count(h)) {
                    s.insert(h);
                    memcpy(v[sz], v[z], sizeof(v[z]));
                    ++v[sz][9];
                    ++sz;
                }
 
                swap(v[z][i + j], v[z][i + j + 1]);
            }
        }
        for (int i = 0; i < 6; i += 3)
            for (int j = 0; j < 3; ++j) {
 
                swap(v[z][i + j], v[z][i + j + 3]);
 
                int h = 0;
                for (int y = 0; y < 9; ++y)
                    h += deg[y] * v[z][y];
                if (!s.count(h)) {
                    s.insert(h);
                    memcpy(v[sz], v[z], sizeof(v[z]));
                    ++v[sz][9];
                    ++sz;
                }
 
                swap(v[z][i + j], v[z][i + j + 3]);
            }
    }
    
}
