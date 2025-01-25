#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x, n;
    cin >> x >> n;
 
    set<int> s;
    multiset<int> ot;
    s.insert(0);
    s.insert(x);
    ot.insert(x);
 
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        auto it1 = s.upper_bound(p);
        auto it2 = it1;
        --it2;
        s.insert(p);
 
        if (*it1 - *it2 - 1 > 0) {
            ot.erase(ot.find(*it1-*it2));
        }
        ot.insert(*it1 - p);
        ot.insert(p - *it2);
        cout << *(--ot.end()) << '\n';
        /*for (auto x : ot) {
            cout << x << ' ';
        }
        cout << endl;*/
    }
 
    return 0;
}
