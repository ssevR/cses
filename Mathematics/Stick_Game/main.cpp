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
 
 
const int N = 1e6 + 1;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
int p[100];
int cur[201];
int gr[N];
 
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; ++i)
        scanf("%d", &p[i]);
 
    gr[0] = 0;
    for (int i = 1; i <= n; ++i) {
        memset(cur, 0, sizeof(cur));
        for (int j = 0; j < k; ++j)
            if (i - p[j] >= 0)
                cur[gr[i - p[j]]] = 1;
        for (int j = 0; j <= k; ++j)
            if (cur[j] == 0) {
                gr[i] = j;
                break;
            }
        if (gr[i] == 0)
            putchar('L');
        else
            putchar('W');
    }
    putchar('\n');

    return 0;
}
