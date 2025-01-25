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
 
int solve(const vector<int>& nums, vector<int>& sums, int x) {
    static vector<int> buffer;
    int n = nums.size();
    buffer.resize(max(int(buffer.size()), 1 << n));
    sums.resize(1 << n);
    sums[0] = 0;
    int size = 1;
    for (int i = 0; i < n; ++i) {
        int with = 0, without = 0;
        int new_size = 0;
        while(without + with < size * 2) {
            if (without < size && (with == size || sums[without] < sums[with] + nums[i])) 
                buffer[new_size++] = sums[without++];
            else 
                buffer[new_size++] = sums[with++] + nums[i];
        }
        while(new_size > 0 && buffer[new_size - 1] > x)
            --new_size;
 
        swap(sums, buffer);
        size = new_size;
    }
    return size;
}
 
int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    int L = n / 2;
    int R = n - L;
    vector<int> left(L), right(R);
    for (int i = 0; i < n; ++i) {
        if (i < L)
            cin >> left[i];
        else
            cin >> right[i - L];
    }
    vector<int> sums_l, sums_r;
 
    int l1 = solve(left, sums_l, x);
    int l2 = solve(right, sums_r, x);
 
 
    ll res = 0;
    for (int i = l1 - 1, j = 0, k = 0; i >= 0; --i) {
        while(j < l2 && sums_l[i] + sums_r[j] < x)
            ++j;
        k = max(k, j);
        while(k < l2 && sums_l[i] + sums_r[k] <= x)
            ++k;
        res += k - j;
    }
    cout << res << '\n';
}
