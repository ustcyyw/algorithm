/**
 * @Time : 2024/9/14-3:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1862F 背包dp
 */
 /*
  * 截止第i天 使用了火攻击共j 是否可能
  * dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]]
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, water, fire, nums[N], sum;

void solve() {
    vector<vector<bool>> dp(n + 1, vector(sum + 1, false));
    dp[0][0] = true;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= sum; j++) {
            dp[i][j] = dp[i - 1][j];
            if(j - nums[i] >= 0) dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i]];
        }
    }
    int ans = INT_MAX;
    for(int j = 0; j <= sum; j++) {
        if(!dp[n][j]) continue;
        int d1 = j % water == 0 ? j / water : j / water + 1;
        int d2 = (sum - j) % fire == 0 ? (sum - j) / fire : (sum - j) / fire + 1;
        ans = min(ans, max(d1, d2));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> water >> fire >> n;
        for (int i = 1; i <= n; i++)
            cin >> nums[i];
        sum = accumulate(nums + 1, nums + n + 1, 0);
        solve();
    }
};