#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    set<int> s;
    for (int i = 0; i < n; ++i) {
        s.insert(i + 1);
    }
 
    auto cur_it = s.begin();
    while(s.size() != 1) {
        auto it =  s.upper_bound(*cur_it);
        if (it == s.end()) {
            it = s.begin();
        }
        int erased = *it;
        cout << erased << ' ';
        s.erase(it);
 
        cur_it =  s.upper_bound(*cur_it);
        if (cur_it == s.end()) {
            cur_it = s.begin();
        }
 
    }
    cout << *s.begin() << '\n';
    return 0;
}
