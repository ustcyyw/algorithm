/**
 * @Time : 2023/10/17-9:36 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 两塔的高度一致 高度差为0
 * dp[i][j]: 截止第i个积木，搭建的两塔之间高度差为j，且较低的那个塔的最高高度
 *
 * 1.不使用积木i dp[i][j] = dp[i-1][j]
 * 2.将积木i放在高塔那边 dp[i][j] = dp[i-1][j-h[i]] if j - h[i] >= 0
 * 3.将积木i放在低塔那边
 * 3.1 低塔依旧低 dp[i][j] = dp[i-1][j+h[i]] + h[i]
 *  低塔加上了h[i]，diff = j，说明原来的差距是j+h[i]
 * 3.2 低塔成为高塔 dp[i][j] = dp[i-1][h[i] - j]
 * 低塔加上了h[i]，diff = j，但是其成为更高的部分，说明原来的差距是 diff_pre = h[i] - j
 * 原低塔的高度是dp[i-1][h[i] - j]，那么高塔的高度就是 dp[i-1][h[i] - j] + diff_pre
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int n, h[N];

int solve() {
    int sum = 0;
    for(int i = 1; i <= n; i++)
        sum += h[i];
    int m = sum / 2 + 1;
    vector<vector<int>> dp(n + 1, vector(m + 1, -1));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            if(j - h[i] >= 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - h[i]]);
            if(j + h[i] <= m && dp[i-1][j + h[i]] != -1)
                dp[i][j] = max(dp[i][j], dp[i-1][j + h[i]] + h[i]);
            if(h[i] - j >= 0 && dp[i-1][h[i] - j] != -1)
                dp[i][j] = max(dp[i][j], dp[i-1][h[i] - j] + h[i] - j);
        }
    }
    return dp[n][0] == 0 ? -1 : dp[n][0];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> h[i];
    cout << solve() << endl;
}