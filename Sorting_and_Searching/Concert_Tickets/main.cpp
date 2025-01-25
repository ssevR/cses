#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
 
using namespace std;
 
int main() {
    int n, m;
    cin >> n >> m;
    multiset<int> h;
    for (int i = 0; i < n; ++i) {
        int cur;
        cin >> cur;
        cur = -cur;
        h.insert(cur);
    }
 
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        auto it = h.lower_bound(-t);
        if (it == h.end()) {
            cout << -1 << '\n';
        }
        else {
            cout << -(*it) << '\n';
            h.erase(it);
        }
        
    }
}
