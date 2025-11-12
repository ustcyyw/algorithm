/**
 * @Time : 2024/3/9-6:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 根据test case猜结论
  * 只允许最多有一种正方形出现2次 其它都只能出现1次 并且有1个长度为1的已经指定了
  * 因为长方形是fbi数列为边长，长为f[n + 1], 宽为f[n]
  * 如果除去一个边长为f[n]的正方形 就得到一个长为f[n], 宽为f[n-1]的长方形
  * 因此猜想 一系列的正方形就是以fbi数列为长度的正方形 并且是连续的
  * 最终只剩一个长为2，宽为1的长方形，拆分为两个边长为1的正方形。
  * 这就是拆分方案，因此是否可行就看指定的x和y在拆分过程种是否一直处于下一个长方形中 直到最后一个长方形
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
int T, n;
ll x, y, f[50];

int init = []() -> int {
    f[0] = f[1] = 1;
    for(int i = 2; i <= 45; i++)
        f[i] = f[i - 1] + f[i - 2];
    return 0;
}();

bool in(ll x1, ll x2, ll y1, ll y2) {
    return x >= x1 && x <= x2 && y >= y1 && y <= y2;
}

bool dfs(ll x1, ll x2, ll y1, ll y2) {
    ll dx = x2 - x1, dy = y2 - y1, d = max(dx, dy) - min(dx, dy);
    if(dx + dy == 1) return true;
    if(dx < dy) {
        if(in(x1, x2, y1, y1 + d - 1)) return dfs(x1, x2, y1, y1 + d - 1);
        if(in(x1, x2, y2 - d + 1, y2)) return dfs(x1, x2, y2 - d + 1, y2);
    } else {
        if(in(x1, x1 + d - 1, y1, y2)) return dfs(x1, x1 + d - 1, y1, y2);
        if(in(x2 - d + 1, x2, y1, y2)) return dfs(x2 - d + 1, x2, y1, y2);
    }
    return false;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> x >> y;
        if(dfs(1, f[n], 1, f[n + 1])) cout << "YES" << "\n";
        else cout << "NO" << "\n";
    }
};