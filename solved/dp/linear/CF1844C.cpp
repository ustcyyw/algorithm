/**
 * @Time : 2025/1/7-12:04 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1844C 1300 动态规划 线性动态规划
 */
/*
  * 动态规划
  * 尝试一下移除操作 发现其实是可以任意选择偶数位置/奇数位置上的元素的
  * 找非空最大子序列和即可
  * dp[i]: 截止i位置的最大非空子序列和
  */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, nums[N];

ll solve() {
    if(n == 1) return nums[1];
    vector<ll> dp(n + 1, 0);
    dp[1] = nums[1], dp[2] = nums[2];
    for(int i = 3; i <= n; i++)
        dp[i] = max({(ll)nums[i], dp[i - 2], dp[i - 2] + nums[i]});
    return max(dp[n - 1], dp[n]);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};