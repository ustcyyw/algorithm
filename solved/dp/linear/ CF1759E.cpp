/**
 * @Time : 2024/8/21-11:05 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1759E 线性动态规划
 */
/*
 * 动态规划
没使用任何药水的 最大值 dp[i][0]
仅使用1次2倍药 dp[i][1]
仅使用1次3倍药 dp[i][2]
仅使用2次2倍药 dp[i][3]
1次2倍 1次3倍 dp[i][4]
都使用        dp[i][5]

dp[i][0] = dp[i - 1][0] + nums[i] / 2, if dp[i - 1][0] > nums[i], else -1
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 9;
typedef long long ll;
ll T, n, h, nums[N];

int solve() {
    vector<vector<ll>> dp(n + 1, vector(6, -1ll));
    dp[0][0] = h, dp[0][1] = 2 * h, dp[0][2] = 3 * h;
    dp[0][3] = 4 * h, dp[0][4] = 6 * h, dp[0][5] = 12 * h;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= 5; j++)
            dp[i][j] = dp[i - 1][j] > nums[i] ? dp[i - 1][j] + nums[i] / 2 : -1;
        dp[i][1] = max(dp[i][1], dp[i][0] * 2);
        dp[i][2] = max(dp[i][2], dp[i][0] * 3);
        dp[i][3] = max(dp[i][3], dp[i][1] * 2);
        dp[i][4] = max({dp[i][4], dp[i][1] * 3, dp[i][2] * 2});
        dp[i][5] = max({dp[i][5], dp[i][4] * 2, dp[i][3] * 3});
    }
    for(int i = n; i >= 0; i--) {
        int flag = 0;
        for(int j = 0; j <= 5; j++)
            if(dp[i][j] > 0) flag = 1;
        if(flag) return i;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> h;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        sort(nums + 1, nums + n + 1);
        cout << solve() << "\n";
    }
};