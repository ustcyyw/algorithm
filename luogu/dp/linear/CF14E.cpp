/**
 * @Time : 2025/1/24-12:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF14E 1900 动态规划
 */
 /*
  * 相邻元素不相同 要能出现"峰"和"谷"，那必然是上升序列和下降序列交替
  * 要满足"峰"、"谷"的数量要求 通过简单画图可以发现
  * 必须是开头为上升序列 结尾为下降序列 峰的数量能比谷多1
  * 如何判断峰和谷就需要知道上一个序列是上升还是下降 以及上一元素和当前元素的值
  * 定义
  * dp[i][j][c][0/1]: 表示截止第i个数 并且是以j结尾 有c个峰
  * 并且第i个元素处于上升/下降（1/0）序列的可能方法数
  *
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 205, mod = 998244353;
int T, n, t;

void solve() {
    if(t > (n - 1) / 2) {
        cout << "0\n";
        return;
    }
    // 最后一个维度为1表示上升阶段 为0表示下降阶段
    vector<vector<vector<vector<ll>>>> dp(n + 1, vector(5, vector(n, vector(2, 0ll))));
    for(int i = 1; i <= 4; i++)
        dp[2][i][0][1] = i - 1;
    for(int i = 3; i <= n; i++) {
        for(int c = 0; c <= t; c++) {
            for(int j = 1; j <= 4; j++) {
                for(int p = 1; p <= 4; p++) {
                    if(p < j) { // 现在是上升阶段的情况
                        dp[i][j][c][1] += dp[i-1][p][c][1] + dp[i-1][p][c][0];
                    } else if(p > j) { // 现在是下降阶段
                        dp[i][j][c][0] += dp[i-1][p][c][0];
                        if(c >= 1) dp[i][j][c][0] += dp[i-1][p][c-1][1];
                    }
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 1; i < 4; i++)
        ans += dp[n][i][t][0];
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> t;
        solve();
    }
};