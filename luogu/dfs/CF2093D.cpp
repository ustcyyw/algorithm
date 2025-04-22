/**
 * @Time : 2025/4/21-11:33 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2093D 1400 递归 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15;
ll T, n, q, pow2[64];
string type;

int init = []() -> int {
    pow2[0] = 1;
    for(int i = 1; i < 62; i++)
        pow2[i] = pow2[i - 1] * 2;
    return 0;
}();

ll dfs1(ll x, ll y, int m) {
    if(m == 0) return 1;
    ll cnt = pow2[2 * m - 2], half = pow2[m - 1];
    if(x > half && y > half) return cnt + dfs1(x - half, y - half, m - 1);
    else if(x <= half && y <= half) return dfs1(x, y, m - 1);
    else if(x > half && y <= half) return 2 * cnt + dfs1(x - half, y, m - 1);
    else return 3 * cnt + dfs1(x, y - half, m - 1);
}

void dfs2(ll d, ll x, ll y, int m) {
    if(m == 0) {
        cout << x << " " << y << "\n";
        return;
    }
    ll cnt = pow2[2 * m - 2], half = pow2[m - 1];
    if(d > 3 * cnt) dfs2(d - 3 * cnt, x, y + half, m - 1);
    else if(d > 2 * cnt) dfs2(d - 2 * cnt, x + half, y , m - 1);
    else if(d > cnt) dfs2(d - cnt, x + half, y + half , m - 1);
    else dfs2(d, x, y, m - 1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> q;
        for(ll i = 1, x, y; i <= q; i++) {
            cin >> type >> x;
            if(type == "->") {
                cin >> y;
                cout << dfs1(x, y, n) << "\n";
            } else dfs2(x, 1, 1, n);
        }
    }
    return 0;
}