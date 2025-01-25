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
// for n >= 8 solution always exist. there are 7 * bin_coef(8, 2) = 448 dif strings for n = 8
string dp[448];
map<string, string> pr;
vector<string> res;
string s;
 
void precompute(int n) {
    int sz = 0;
    for (int k = 0; k <= (n < 8); ++k) // if n < 8 parity of pos .. does matter
        for (int i = 0; i <= n - 2; ++i) {
            string cur = string(i, 'A') + string(n - 2 - i, 'B');
            cur.insert(k, "..");
            dp[sz++] = cur;
            pr[cur] = "";
        }
 
    int i = 0;
    while(i < sz) {
        string cur = dp[i++];
        int k = cur.find('.');
        for (int i = 0; i < n - 1; ++i) {
            if (cur[i] != '.' && cur[i + 1] != '.') {
                string nxt = cur;
                swap(nxt[i], nxt[k]);
                swap(nxt[i + 1], nxt[k + 1]);
                if (!pr.count(nxt)) {
                    pr[nxt] = cur;
                    dp[sz++] = nxt;
                }
            }
        }
    }
    // for n = 8 sz is 448
}
 
void solve(int l, int r) {
    string cur = s.substr(l, r - l);
    while(pr[cur] != "") {
        cur = pr[cur];
        res.push_back(s.substr(0, l) + cur + s.substr(r));
    }
    s = s.substr(0, l) + cur + s.substr(r);
}
 
int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
 
    cin >> s;
    if (n * 2 < 8) {
        precompute(n * 2);
        if (!pr.count(s)) {
            cout << "-1\n";
            return 0;
        }
        solve(0, n * 2);
    }
    else {
        int k = s.find('.');
        if (k > 1) {
            swap(s[k], s[0]);
            swap(s[k + 1], s[1]);
            res.push_back(s);
        }
 
        precompute(8);
        int l = 0, r = 2 * n;
        while(r - l > 8) {
            if (s[l + 2] == 'A' && s[l + 3] == 'A') {
                swap(s[l], s[l + 2]);
                swap(s[l + 1], s[l + 3]);
                res.push_back(s);
                l += 2;
            }
            else if (s[r - 1] == 'B' && s[r - 2] == 'B') {
                r -= 2;
            }
            else {
                int b_pos = s.find('B', l); // bpos <= l + 1
                int a_pos = s.find('A', b_pos + 2); // apos = 2 * n - 1 is possible
                int flag = 0;
                if (a_pos == 2 * n - 1) { 
                    --a_pos;
                    flag = 1;
                    // s[a_pos, a_pos + 1] == "BA"
                }
 
                swap(s[l], s[b_pos]);
                swap(s[l + 1], s[b_pos + 1]);
                res.push_back(s);
 
                swap(s[b_pos], s[a_pos]);
                swap(s[b_pos + 1], s[a_pos + 1]);
                res.push_back(s);
 
                swap(s[a_pos], s[l]);
                swap(s[a_pos + 1], s[l + 1]);
                res.push_back(s);
 
                if (flag) solve(l, l + 8);
            }
        }
        solve(l, l + 8);
    }
 
    cout << res.size() << '\n';
    for (auto& x : res) 
        cout << x << '\n';

    return 0;
}
