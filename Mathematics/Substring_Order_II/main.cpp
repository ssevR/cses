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
 
struct State {
    int len;            // Length of the longest substring ending here
    int link;           // Suffix link
    int cnt;            // number of substrings that end in state
    ll num;             // number of substrings that end in state and its descendants
    array<int, 26> transitions; // Transitions for 'a'-'z' (index 0-25)
    State() : len(0), link(-1), cnt(0) { transitions.fill(-1); }
};
 
class SuffixAutomaton {
public:
    vector<State> states;
    vector<bool> used;
    int last;
 
    SuffixAutomaton() {
        states.emplace_back();
        last = 0;
    }
 
    void extend(char c) {
        int cur = states.size();
        states.emplace_back();
        states[cur].len = states[last].len + 1;
        states[cur].cnt = 1;
 
        int p = last;
        int idx = c - 'a'; // Convert char to 0-25 index
 
        // Update transitions for states along the suffix link path
        while (p >= 0 && states[p].transitions[idx] == -1) {
            states[p].transitions[idx] = cur;
            p = states[p].link;
        }
 
        if (p == -1) {
            states[cur].link = 0;
        } else {
            int q = states[p].transitions[idx];
            if (states[p].len + 1 == states[q].len) {
                states[cur].link = q;
            } else {
                int clone = states.size();
                states.emplace_back();
                states[clone].len = states[p].len + 1;
                states[clone].transitions = states[q].transitions; // Copy transitions
                states[clone].link = states[q].link;
 
                while (p >= 0 && states[p].transitions[idx] == q) {
                    states[p].transitions[idx] = clone;
                    p = states[p].link;
                }
 
                states[q].link = states[cur].link = clone;
            }
        }
        last = cur;
    }
 
    void dfs(int v) {
        used[v] = true;
        states[v].num = states[v].cnt;
        for (auto u : states[v].transitions) {
            if (u != -1 && !used[u])
                dfs(u);
            if (u != -1) { 
                states[v].num += states[u].num;
            }
        }
 
 
 
    };
 
    void compute_counts() {
        // Sort states by length in descending order
        vector<int> order(states.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return states[a].len > states[b].len;
        });
 
        // Propagate counts via suffix links
        for (int u : order) {
            if (states[u].link != -1) {
                states[states[u].link].cnt += states[u].cnt;
            }
        }
        states[0].cnt = 0;
    }
 
    void build(const string& s) {
        for (char c : s) {
            extend(c);
        }
        used.assign(states.size(), false);
        compute_counts();
        dfs(0);
 
    }
    string find_k(ll k) {
        int v = 0;
        string s;
 
        while(k > states[v].cnt) {
            for (int i = 0; i < 26; ++i) {
                int u = states[v].transitions[i];
                if (u == -1) {
                    continue;
                }
                else if (k <= states[u].num + states[v].cnt) {
                    k -= states[v].cnt;
                    s += char('a' + i);
                    v = u;
                    break;
                }
                else {
                    k -= states[u].num;
                }
            }
        }
 
        return s;
    }
 
};
 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
 
int main() {
    IOS;
    SuffixAutomaton sa;
    string s;
    cin >> s;
    sa.build(s);
    ll k;
    cin >> k;
    cout << sa.find_k(k) << '\n';
    
}
