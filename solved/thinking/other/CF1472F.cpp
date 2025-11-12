/**
 * @Time : 2024/7/8-9:43 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1472F 找规律
 */
 /*
  * 画图找规律
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m;
vector<vector<int>> pos;

bool solve() {
    sort(pos.begin(), pos.end());
    pos.push_back({n + 1, 1}), pos.push_back({n + 1, 2}); // 设置哨兵
    for(int i = 0; i < m; i += 2) {
        int c1 = pos[i][0], r1 = pos[i][1];
        int c2 = pos[i + 1][0], r2 = pos[i + 1][1];
        if(c1 == c2) continue;
        int c3 = pos[i + 2][0], r3 = pos[i + 2][1];
        if(c2 == c3) return false;
        if(r1 != r2) {
            if((c2 - c1) % 2 != 0) return false;
        } else {
            if((c2 - c1) % 2 == 0) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        pos = {};
        for(int i = 1, r, c; i <= m; i++) {
            cin >> r >> c;
            pos.push_back({c, r});
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};