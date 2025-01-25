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
const int dy[4] = {1,0,-1,0}, dx[4] = {0,1,0,-1} ;
char F[4] = {'D', 'R', 'U', 'L'};
int P[256];
 
string pr[6][6][6][6][6][6];
 
bool is_solvable(int n, int m, int sy, int sx, int ty, int tx) {
    if (n == 1 && m == 1)
        return true;
    if (sy == ty && sx == tx)
        return false;
 
    if (n > m) {
        swap(n, m);
        swap(sy, sx);
        swap(ty, tx);
    }
    if (sx > tx) {
        swap(sx, tx);
        swap(sy, ty);
    }
    if (n == 1) {
        if (sx == 0 && tx == m - 1)
            return true;
        else
            return false;
    }
    else if (n == 2) {
        if (sx == tx && (sx == 0 || sx == m - 1))
            return true;
        else if (sx == tx)
            return false;
 
        if ((sx + sy) % 2 == (tx + ty) % 2)
            return false;
        else
            return true;
    }
    else if ((n * m) % 2 == 1) {
        if ((sx + sy) % 2 == 0 && (tx + ty) % 2 == 0)
            return true;
        else
            return false;
    }
    else if (n == 3) {
        if ((sx + sy) % 2 == (tx + ty) % 2)
            return false;
        if ((sx + sy) % 2 == 1 && (sx < tx - 1 || (sy == 1 && sx < tx)))
            return false;
        if ((tx + ty) % 2 == 1 && (tx < sx - 1 || (ty == 1 && tx < sx)))
            return false;
        return true;
 
    }
    else {
        if ((sx + sy) % 2 == (tx + ty) % 2)
            return false;
        else
            return true;
    }
}
 
string solve(int n, int m, int sy, int sx, int ty, int tx) {
    if (n > m) {
        int tmpy, tmpx;
 
        tmpx = sy;
        tmpy = m - sx - 1;
        sx = tmpx;
        sy = tmpy;
 
        tmpx = ty;
        tmpy = m - tx - 1;
        tx = tmpx;
        ty = tmpy;
 
        swap(n, m);
        auto res = solve(n, m, sy, sx, ty, tx);
 
        for (int i = 0; i < int(res.size()); ++i) {
            res[i] = F[(int(P[res[i]]) + 3) % 4];
        }
        return res;
    }
    if (sx > tx) {
        sx = m - sx - 1;
        tx = m - tx - 1;
        auto res = solve(n, m, sy, sx, ty, tx);
        for (int i = 0; i < int(res.size()); ++i) {
            if (res[i] == 'L')
                res[i] = 'R';
            else if (res[i] == 'R')
                res[i] = 'L';
        }
        return res;
    }
    if (sy > ty) {
        sy = n - sy - 1;
        ty = n - ty - 1;
        auto res = solve(n, m, sy, sx, ty, tx);
        for (int i = 0; i < res.size(); ++i) {
            if (res[i] == 'U')
                res[i] = 'D';
            else if (res[i] == 'D')
                res[i] = 'U';
        }
        return res;
    }
 
    if (n == 1) {
        string res;
        for (int i = 0; i < m - 1; ++i)
            res += 'R';
        return res;
    }
    if (n == 2 && sy == ty && sx + 1 == tx) {
        string res;
        if (sy == 0) {
            for (int i = 0; i < sx; ++i)
                res += 'L';
            res += 'D';
            for (int i = 0; i < m - 1; ++i)
                res += 'R';
            res += 'U';
            for (int i = m - 1; i > tx; --i)
                res += 'L';
        }
        else {
            for (int i = 0; i < sx; ++i)
                res += 'L';
            res += 'U';
            for (int i = 0; i < m - 1; ++i)
                res += 'R';
            res += 'D';
            for (int i = m - 1; i > tx; --i)
                res += 'L';
        }
        return res;
    }
    if (n <= 4 && m <= 5) {
        return pr[n][m][sy][sx][ty][tx];
    }
    if (sx >= 2 && is_solvable(n, m - 2, sy, sx - 2, ty, tx - 2)) {
        auto res = solve(n, m - 2, sy, sx - 2, ty, tx - 2);
        pii cur = {sy, sx - 2};
        for (int i = 0; i < res.size(); ++i) {
            pii next = {cur.fi + dy[P[res[i]]], cur.se + dx[P[res[i]]]};
            if (cur.se == 0 && next.se == 0) {
                return res.substr(0, i) + "L" + solve(n, 2, cur.fi, 1, next.fi, 1) + "R" + res.substr(i + 1, res.size());
            }
            cur = next;
        }
    }
    if (tx <= m - 3 && is_solvable(n, m - 2, sy, sx, ty, tx)) {
        auto res = solve(n, m - 2, sy, sx, ty, tx);
        pii cur = {sy, sx};
        for (int i = 0; i < res.size(); ++i) {
            pii next = {cur.fi + dy[P[res[i]]], cur.se + dx[P[res[i]]]};
            if (cur.se == m - 3 && next.se == m - 3) {
                return res.substr(0, i) + "R" + solve(n, 2, cur.fi, 0, next.fi, 0) + "L" + res.substr(i + 1, res.size());
            }
            cur = next;
        }
    }
 
    for (int i = sy; i < ty; ++i)
        for (int j = 0; j < m; ++j) 
            if (is_solvable(i + 1, m, sy, sx, i, j) && is_solvable(n - i - 1, m, 0, j, ty - (i + 1), tx)) {
                auto res1 = solve(i + 1, m, sy, sx, i, j);
                auto res2 = solve(n - i - 1, m, 0, j, ty - (i + 1), tx);
                return res1 + "D" + res2;
            }
 
    for (int j = sx; j < tx; ++j)
        for (int i = 0; i < n; ++i) 
            if (is_solvable(n, j + 1, sy, sx, i, j) && is_solvable(n, m - j - 1, i, 0, ty, tx - (j + 1))) {
                auto res1 = solve(n, j + 1, sy, sx, i, j);
                auto res2 = solve(n, m - j - 1, i, 0, ty, tx - (j + 1));
                return res1 + "R" + res2;
            }
}
 
 
bool checker(int n, int m, int sy, int sx, int ty, int tx, string res) {
    if (res.size() != n * m - 1)
        return false;
    vector<vector<int> > used(n, vector<int>(m));
    int y = sy, x = sx;
    for (int i = 0; i < n * m - 1; ++i) {
        if ( y < 0 || y >= n || x < 0 || x >= m || used[y][x])
            return false;
        used[y][x] = 1;
        int f = P[res[i]];
        y += dy[f];
        x += dx[f];
    }
    if (y != ty || x != tx)
        return false;
    return true;
}
 
int main() {
    IOS;
 
    P['D'] = 0;
    P['R'] = 1;
    P['U'] = 2;
    P['L'] = 3;
 
    pr[2][2][0][0][0][1] = "DRU";
    pr[2][2][0][0][1][0] = "RDL";
    pr[2][2][0][1][1][1] = "LDR";
    pr[2][2][1][0][1][1] = "URD";
    pr[2][3][0][0][0][1] = "DRRUL";
    pr[2][3][0][0][1][0] = "RRDLL";
    pr[2][3][0][0][1][2] = "DRURD";
    pr[2][3][0][1][0][2] = "LDRRU";
    pr[2][3][0][2][1][2] = "LLDRR";
    pr[2][3][1][0][1][1] = "URRDL";
    pr[2][3][1][1][1][2] = "LURRD";
    pr[2][4][0][0][0][1] = "DRRRULL";
    pr[2][4][0][0][0][3] = "DRURDRU";
    pr[2][4][0][0][1][0] = "RRRDLLL";
    pr[2][4][0][0][1][2] = "DRURRDL";
    pr[2][4][0][1][0][2] = "LDRRRUL";
    pr[2][4][0][1][1][3] = "LDRRURD";
    pr[2][4][0][2][0][3] = "LLDRRRU";
    pr[2][4][0][3][1][3] = "LLLDRRR";
    pr[2][4][1][0][1][1] = "URRRDLL";
    pr[2][4][1][0][1][3] = "URDRURD";
    pr[2][4][1][1][1][2] = "LURRRDL";
    pr[2][4][1][2][1][3] = "LLURRRD";
    pr[2][5][0][0][0][1] = "DRRRRULLL";
    pr[2][5][0][0][0][3] = "DRURDRRUL";
    pr[2][5][0][0][1][0] = "RRRRDLLLL";
    pr[2][5][0][0][1][2] = "DRURRRDLL";
    pr[2][5][0][0][1][4] = "DRURDRURD";
    pr[2][5][0][1][0][2] = "LDRRRRULL";
    pr[2][5][0][1][0][4] = "LDRRURDRU";
    pr[2][5][0][1][1][3] = "LDRRURRDL";
    pr[2][5][0][2][0][3] = "LLDRRRRUL";
    pr[2][5][0][2][1][4] = "LLDRRRURD";
    pr[2][5][0][3][0][4] = "LLLDRRRRU";
    pr[2][5][0][4][1][4] = "LLLLDRRRR";
    pr[2][5][1][0][1][1] = "URRRRDLLL";
    pr[2][5][1][0][1][3] = "URDRURRDL";
    pr[2][5][1][1][1][2] = "LURRRRDLL";
    pr[2][5][1][1][1][4] = "LURRDRURD";
    pr[2][5][1][2][1][3] = "LLURRRRDL";
    pr[2][5][1][3][1][4] = "LLLURRRRD";
    pr[3][3][0][0][0][2] = "RDLDRRUU";
    pr[3][3][0][0][1][1] = "RRDDLLUR";
    pr[3][3][0][0][2][0] = "RRDDLULD";
    pr[3][3][0][0][2][2] = "RRDLLDRR";
    pr[3][3][0][2][2][2] = "LLDDRURD";
    pr[3][3][1][1][2][2] = "RULLDDRR";
    pr[3][3][2][0][2][2] = "UURRDLDR";
    pr[3][4][0][0][0][1] = "DDRURDRUULL";
    pr[3][4][0][0][0][3] = "RRDLLDRRRUU";
    pr[3][4][0][0][1][0] = "RRRDDLULDLU";
    pr[3][4][0][0][1][2] = "RRRDDLLLURR";
    pr[3][4][0][0][2][1] = "RRRDDLULLDR";
    pr[3][4][0][0][2][3] = "RRRDLLLDRRR";
    pr[3][4][0][1][0][2] = "LDDRURDRUUL";
    pr[3][4][0][1][1][1] = "LDDRRRUULDL";
    pr[3][4][0][1][2][2] = "LDDRURURDDL";
    pr[3][4][0][2][0][3] = "LLDDRURDRUU";
    pr[3][4][0][2][1][2] = "RDDLLLUURDR";
    pr[3][4][0][2][2][3] = "RDLLULDDRRR";
    pr[3][4][0][3][1][3] = "LLLDDRURDRU";
    pr[3][4][1][0][2][0] = "URRRDDLULDL";
    pr[3][4][1][1][1][2] = "ULDDRRRUULD";
    pr[3][4][1][1][2][1] = "RDRUULLLDDR";
    pr[3][4][1][1][2][3] = "ULDDRRUURDD";
    pr[3][4][1][2][2][2] = "LDLUURRRDDL";
    pr[3][4][1][3][2][3] = "ULLLDDRURDR";
    pr[3][4][2][0][2][1] = "UURRRDDLULD";
    pr[3][4][2][0][2][3] = "UURRRDLLDRR";
    pr[3][4][2][1][2][2] = "LUURDRURDDL";
    pr[3][4][2][2][2][3] = "ULDLUURRRDD";
    pr[3][5][0][0][0][2] = "RDLDRRURDRUULL";
    pr[3][5][0][0][0][4] = "RRRDLLLDRRRRUU";
    pr[3][5][0][0][1][1] = "RRRRDDLULDLLUR";
    pr[3][5][0][0][1][3] = "RRRRDDLLLLURRR";
    pr[3][5][0][0][2][0] = "RRRRDDLULDLULD";
    pr[3][5][0][0][2][2] = "RRRRDDLULLLDRR";
    pr[3][5][0][0][2][4] = "RRRRDLLLLDRRRR";
    pr[3][5][0][2][0][4] = "LLDDRURDRRULUR";
    pr[3][5][0][2][1][3] = "LLDDRURDRRUULD";
    pr[3][5][0][2][2][2] = "LLDDRURRURDDLL";
    pr[3][5][0][2][2][4] = "LLDDRURDRUURDD";
    pr[3][5][0][4][2][4] = "LLLLDDRURDRURD";
    pr[3][5][1][1][1][3] = "ULDDRRUURRDDLU";
    pr[3][5][1][1][2][2] = "RRDRUULLLLDDRR";
    pr[3][5][1][1][2][4] = "ULDDRRUURRDLDR";
    pr[3][5][1][3][2][4] = "RULLLLDDRURDRR";
    pr[3][5][2][0][2][2] = "UURRRRDDLULLDR";
    pr[3][5][2][0][2][4] = "UURRRRDLLLDRRR";
    pr[3][5][2][2][2][4] = "ULDLUURRRRDLDR";
    pr[4][4][0][0][0][1] = "DRRDLLDRRRUUULL";
    pr[4][4][0][0][0][3] = "RRDLLDDRURDRUUU";
    pr[4][4][0][0][1][0] = "RRRDLLDRRDLLLUU";
    pr[4][4][0][0][1][2] = "RRRDDDLULDLUURR";
    pr[4][4][0][0][2][1] = "RRRDLLLDDRRRULL";
    pr[4][4][0][0][2][3] = "RRRDLLLDDRURDRU";
    pr[4][4][0][0][3][0] = "RRRDLLLDRRRDLLL";
    pr[4][4][0][0][3][2] = "RRRDLLLDDRURRDL";
    pr[4][4][0][1][0][2] = "LDRRDLLDRRRUUUL";
    pr[4][4][0][1][1][1] = "LDDDRURDRUUULDL";
    pr[4][4][0][1][1][3] = "LDRDLDRRRULUURD";
    pr[4][4][0][1][2][2] = "LDRRURDDDLLLURR";
    pr[4][4][0][1][3][1] = "LDRRURDDDLULLDR";
    pr[4][4][0][1][3][3] = "LDRRURDDLLLDRRR";
    pr[4][4][0][2][0][3] = "LLDRRDLLDRRRUUU";
    pr[4][4][0][2][1][2] = "RDDDLULDLUUURDR";
    pr[4][4][0][2][2][3] = "RDLLULDDDRURDRU";
    pr[4][4][0][2][3][2] = "RDLLULDDDRURRDL";
    pr[4][4][0][3][1][3] = "LLLDRRDLLDRRRUU";
    pr[4][4][0][3][3][3] = "LLLDRRRDLLLDRRR";
    pr[4][4][1][0][1][1] = "URRRDLDRDLLLURU";
    pr[4][4][1][0][1][3] = "URDDLDRRRULUURD";
    pr[4][4][1][0][2][0] = "URRRDLLDRRDLLLU";
    pr[4][4][1][0][2][2] = "URRRDLLDLDRRRUL";
    pr[4][4][1][0][3][1] = "URRRDDDLUULDLDR";
    pr[4][4][1][0][3][3] = "URRRDLLDLDRRURD";
    pr[4][4][1][1][1][2] = "ULDDDRURDRUUULD";
    pr[4][4][1][1][2][1] = "ULDDDRRRUUULDDL";
    pr[4][4][1][1][2][3] = "LURRRDLDLLDRRRU";
    pr[4][4][1][1][3][2] = "ULDDDRURUURDDDL";
    pr[4][4][1][2][1][3] = "LDRRDLLLUUURRRD";
    pr[4][4][1][2][2][2] = "URDDDLLLUUURDDR";
    pr[4][4][1][2][3][3] = "URDDLLUULDDDRRR";
    pr[4][4][1][3][2][3] = "ULLLDRRDLLDRRRU";
    pr[4][4][2][0][2][1] = "DRRRUUULLLDRRDL";
    pr[4][4][2][0][2][3] = "DRUULURRRDLDDRU";
    pr[4][4][2][0][3][0] = "UURRRDLLDRRDLLL";
    pr[4][4][2][0][3][2] = "DRUULURRRDLDRDL";
    pr[4][4][2][1][2][2] = "UULDDDRRRUUULDD";
    pr[4][4][2][1][3][1] = "URDDRUUULLLDDDR";
    pr[4][4][2][1][3][3] = "UULDDDRRUUURDDD";
    pr[4][4][2][2][2][3] = "URULLLDRDLDRRRU";
    pr[4][4][2][2][3][2] = "ULDDLUUURRRDDDL";
    pr[4][4][2][3][3][3] = "UULLLDRRDLLDRRR";
    pr[4][4][3][0][3][1] = "UUURRRDLLDRRDLL";
    pr[4][4][3][0][3][3] = "UUURRRDLLDDRURD";
    pr[4][4][3][1][3][2] = "LUUURRRDLLDRRDL";
    pr[4][4][3][2][3][3] = "UULDDLUUURRRDDD";
    pr[4][5][0][0][0][1] = "DRRRDLLLDRRRRUUULLL";
    pr[4][5][0][0][0][3] = "RRDLLDDRURDRRULURUL";
    pr[4][5][0][0][1][0] = "RRRRDLLLDRRRDLLLLUU";
    pr[4][5][0][0][1][2] = "RRRRDLDRDLLULDLUURR";
    pr[4][5][0][0][1][4] = "RRDLLDDRURDRRULUURD";
    pr[4][5][0][0][2][1] = "RRRRDLLLLDDRRRRULLL";
    pr[4][5][0][0][2][3] = "RRRRDLLLLDDRURDRRUL";
    pr[4][5][0][0][3][0] = "RRRRDLLLLDRRRRDLLLL";
    pr[4][5][0][0][3][2] = "RRRRDLLLLDDRURRRDLL";
    pr[4][5][0][0][3][4] = "RRRRDLLLLDDRURDRURD";
    pr[4][5][0][1][0][2] = "LDRRRDLLLDRRRRUUULL";
    pr[4][5][0][1][0][4] = "LDRRURDDLLLDRRRRUUU";
    pr[4][5][0][1][1][1] = "LDDDRURDRRULURULLDL";
    pr[4][5][0][1][1][3] = "LDRRURRDDDLLLLURRRU";
    pr[4][5][0][1][2][2] = "LDRRURRDLDRDLLLLURR";
    pr[4][5][0][1][2][4] = "LDRRURRDLDLLLDRRRRU";
    pr[4][5][0][1][3][1] = "LDRRURRDLDRDLLULLDR";
    pr[4][5][0][1][3][3] = "LDRDLDRRUUURRDLDRDL";
    pr[4][5][0][2][0][3] = "LLDRRRDLLLDRRRRUUUL";
    pr[4][5][0][2][1][2] = "LLDRDLDRRURDRUUULDL";
    pr[4][5][0][2][1][4] = "LLDRRDLLDRRRRULUURD";
    pr[4][5][0][2][2][3] = "LLDRRRURDDDLLLLURRR";
    pr[4][5][0][2][3][2] = "LLDRRRURDDDLULLLDRR";
    pr[4][5][0][2][3][4] = "LLDRRRURDDLLLLDRRRR";
    pr[4][5][0][3][0][4] = "LLLDRRRDLLLDRRRRUUU";
    pr[4][5][0][3][1][3] = "RDDDLULDLLURULURRDR";
    pr[4][5][0][3][2][4] = "RDLLULLDRDLDRRURDRU";
    pr[4][5][0][3][3][3] = "RDLLULLDRDLDRRURRDL";
    pr[4][5][0][4][1][4] = "LLLLDRRRDLLLDRRRRUU";
    pr[4][5][0][4][3][4] = "LLLLDRRRRDLLLLDRRRR";
    pr[4][5][1][0][1][1] = "URRRRDLLDRRDLLLLURU";
    pr[4][5][1][0][1][3] = "URRRRDDDLULDLLURURR";
    pr[4][5][1][0][2][0] = "URRRRDLLLDRRRDLLLLU";
    pr[4][5][1][0][2][2] = "URRRRDLLLDLDRRRRULL";
    pr[4][5][1][0][2][4] = "URRRRDLLLDLDRRURDRU";
    pr[4][5][1][0][3][1] = "URRRRDLDRDLLUULDLDR";
    pr[4][5][1][0][3][3] = "URRRRDLLLDLDRRURRDL";
    pr[4][5][1][1][1][2] = "ULDDDRURDRRULURULLD";
    pr[4][5][1][1][1][4] = "ULDDDRURDRRULULURRD";
    pr[4][5][1][1][2][1] = "ULDDDRRRRUUULLDRDLL";
    pr[4][5][1][1][2][3] = "ULDDDRURDRRUUULLDRD";
    pr[4][5][1][1][3][2] = "ULDDDRURUURRDLDRDLL";
    pr[4][5][1][1][3][4] = "ULDDDRURDRUULURRDDD";
    pr[4][5][1][2][1][3] = "ULLDRDLDRRURDRUUULD";
    pr[4][5][1][2][2][2] = "ULLDRDLDRRRRUUULDDL";
    pr[4][5][1][2][2][4] = "URRDLDLLUULDDDRRRRU";
    pr[4][5][1][2][3][3] = "ULLDRDLDRRURUURDDDL";
    pr[4][5][1][3][1][4] = "LLDRRRDLLLLUUURRRRD";
    pr[4][5][1][3][2][3] = "URDDDLLLLUUURRDLDRR";
    pr[4][5][1][3][3][4] = "URDDLLUULLDRDLDRRRR";
    pr[4][5][1][4][2][4] = "ULLLLDRRRDLLLDRRRRU";
    pr[4][5][2][0][2][1] = "DRRUURDDRUUULLLLDRD";
    pr[4][5][2][0][2][3] = "DRUULURRRRDLLDDRRUL";
    pr[4][5][2][0][3][0] = "UURRRRDLLLDRRRDLLLL";
    pr[4][5][2][0][3][2] = "DRUULURRRRDLLDRRDLL";
    pr[4][5][2][0][3][4] = "DRUULURRRRDLLDDRURD";
    pr[4][5][2][1][2][2] = "UULDDDRRRRUUULLDRDL";
    pr[4][5][2][1][2][4] = "UULDDDRRUUURRDLDDRU";
    pr[4][5][2][1][3][1] = "URRDLDRRUUULLLLDDDR";
    pr[4][5][2][1][3][3] = "UULDDDRRUUURRDLDRDL";
    pr[4][5][2][2][2][3] = "UULLDRDLDRRRRUUULDD";
    pr[4][5][2][2][3][2] = "ULDDLUUURRRRDLDRDLL";
    pr[4][5][2][2][3][4] = "UULLDRDLDRRRUUURDDD";
    pr[4][5][2][3][2][4] = "URULLLLDRRDLLDRRRRU";
    pr[4][5][2][3][3][3] = "ULLDRDLLUUURRRRDDDL";
    pr[4][5][2][4][3][4] = "UULLLLDRRRDLLLDRRRR";
    pr[4][5][3][0][3][1] = "UUURRRRDLLLDRRRDLLL";
    pr[4][5][3][0][3][3] = "UUURRRRDLLLDDRURRDL";
    pr[4][5][3][1][3][2] = "LUUURRRRDLLLDRRRDLL";
    pr[4][5][3][1][3][4] = "LUUURRRRDLLLDRDRURD";
    pr[4][5][3][2][3][3] = "UULDDLUUURRRRDLDRDL";
    pr[4][5][3][3][3][4] = "UULLDRDLLUUURRRRDDD";
 
    int t;
    cin >> t;
    while(t--) {
        int n, m, sy, sx, ty, tx;
        cin >> n >> m >> sy >> sx >> ty >> tx;
        --sy, --sx, --ty, --tx;
 
        if (is_solvable(n, m, sy, sx, ty, tx)) {
            cout << "YES\n";
            auto res = solve(n, m, sy, sx, ty, tx);
            cout << res << '\n';
        }
        else {
            cout << "NO\n";
        }
    }
}
