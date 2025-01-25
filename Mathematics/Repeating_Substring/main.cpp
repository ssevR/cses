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
 
void radix_sort(vector<pair<pii, int> >& v) {
    int n = v.size();
    {
        vector<int> cnt(n);
        for (int i = 0; i < n; ++i) {
            ++cnt[v[i].first.second];
        }
 
        vector<int> pos(n);
        for (int i = 1; i < n; ++i) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
 
        vector<pair<pii, int> > v_new(n);
        for (int i = 0; i < n; ++i) {
            v_new[pos[v[i].first.second]] = v[i];
            ++pos[v[i].first.second];
        }
        v = v_new;
    }
 
 
    {
        vector<int> cnt(n);
        for (int i = 0; i < n; ++i) {
            ++cnt[v[i].first.first];
        }
 
        vector<int> pos(n);
        for (int i = 1; i < n; ++i) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
 
        vector<pair<pii, int> > v_new(n);
        for (int i = 0; i < n; ++i) {
            v_new[pos[v[i].first.first]] = v[i];
            ++pos[v[i].first.first];
        }
        v = v_new;
    }
}
 
pair<vector<int>, vector<int> > calc_suf(string s) {
    s += '$';
    int n = s.size();
 
    vector<pair<pii, int> > v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = {{s[i], s[i]}, i};
    }
 
    vector<int> c(n);
 
 
    sort(v.begin(), v.end());
 
    for (int i = 0; (1 << i) <= n; ++i) {
        int cnt_class = 0;
        pii last = v[0].first;
        for (int j = 0; j < n; ++j) {
            if (v[j].first.first != last.first || v[j].first.second != last.second) {
                ++cnt_class;
            }
            last = v[j].first;
            v[j].first.first = cnt_class;
        }
 
        for (int j = 0; j < n; ++j) {
            c[v[j].second] = v[j].first.first;
        }
 
        for (int j = 0; j < n; ++j) {
            v[j].first.second = c[(v[j].second + (1 << i)) % n];
        }
        radix_sort(v);
    }
 
    vector<int> suf_arr(n);
    for (int i = 0; i < n; ++i) {
        suf_arr[i] = v[i].second;
        c[suf_arr[i]] = i;
    }
 
    vector<int> lcp(n - 1);
    int k = 0;
    for (int i = 0; i < n - 1; ++i) {
        int pi = c[i];
        int j = suf_arr[pi - 1];
        // lcp[i] = lcp(s[i..], s[j..])
 
        while(s[i + k] == s[j + k]) {
            ++k;
        }
        lcp[pi - 1] = k;
 
        k = max(0, k - 1);
    }
 
    return {suf_arr, lcp};
}
 
 
int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    auto [suf, lcp] = calc_suf(s);
 
    int len = 0;
    pii res = {0, 0};
    for (int i = 0; i < n; ++i) {
        if (lcp[i] > res.fi) {
            res = {lcp[i], suf[i]};
        }
    }
    if (res.fi == 0)
        cout << -1 << '\n';
    cout << s.substr(res.se, res.fi) << '\n';

    return 0;
}
