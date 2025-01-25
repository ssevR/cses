#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
 
int main() {
    int n;
    cin >> n;
    int res = 0;
    multiset<int> s;
    for (int i = 0; i < n; ++i) {
        int cur;
        cin >> cur;
        auto it = s.upper_bound(cur);
        if (it != s.end()) {
            s.erase(it);
        }
        s.insert(cur);
    }
    cout << s.size() << '\n';
}
