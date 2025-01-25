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
 
 
//source https://cp-algorithms.com/string/manacher.html
//checker https://judge.yosupo.jp/problem/enumerate_palindromes
//submit https://judge.yosupo.jp/submission/232295
 
vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
 
vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}
// x - 1 is length
 
/*int main() {
    string s;
    cin >> s;
    auto v = manacher(s);
    for (auto x : v) {
        cout << x - 1 << ' ';
    }
    cout << '\n';
    return 0;
}*/
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    string s;
    cin >> s;
    auto v = manacher(s);
    int res = 1;
    for (int i = 0; i < v.size(); ++i) {
        res = max(res, v[i] - 1);
    }
    for (int i = 0; i < v.size(); ++i) {
        if (res == v[i] - 1) {
            if (i % 2 == 0) {
                cout << s.substr(i/2 - res/2, res) << '\n';
            }
            else {
                cout << s.substr(i/2 - res/2 + 1, res) << '\n';
            }
            return 0;
        }
    }
}
