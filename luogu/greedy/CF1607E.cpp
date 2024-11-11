/**
 * @Time : 2024/7/18-1:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1607E 贪心 实现
 */
 /*
  * 上下左右相对于起点会有偏移量 通过调整起点 让偏移量不至于跑到边界外
  * 为了执行更多命令 只能按顺序处理偏移量
  * up down left right 分别记录起点的上下左右取值范围
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e6 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m;
string s;

void solve() {
    int up = 1, down = n, left = 1, right = m, ax = -1, ay = -1;
    for(int i = 0, x = 0, y = 0; i < s.size(); i++) {
        if(s[i] == 'L') y--;
        if(s[i] == 'R') y++;
        if(s[i] == 'U') x--;
        if(s[i] == 'D') x++;
        if(y > 0) right = min(right, m - y);
        else left = max(left, 1 - y);
        if(x > 0) down = min(down, n - x);
        else up = max(up, 1 - x);
        if(left > right || up > down) break;
        if(up == down) ax = up;
        if(left == right) ay = left;
    }
    if(ax == -1) ax = min(up, n);
    if(ay == -1) ay = min(m, left);
    cout << ax << " " << ay << "\n";
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> s;
        solve();
    }
};