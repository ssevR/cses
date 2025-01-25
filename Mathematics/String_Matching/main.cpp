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
 
 
vector<int> prefix_function(const string& s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
 
// all occurrences of the string  s  in the text  t
vector<int> kmp(const string& t, const string& s) { 
 
    string f = s + "#" + t;
    auto pi = prefix_function(f);
 
    vector<int> res;
    int l = s.size();
    for (int i = l + 1; i < f.size(); ++i) {
        if (pi[i] == l)
            res.push_back(i - (l + 1) - (l - 1));
    }
    return res;
}
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    string a, b;
    cin >> a >> b;
    cout << kmp(a, b).size() << '\n';

    return 0;
}
