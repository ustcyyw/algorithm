/**
 * @Time : 2024/12/30-4:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1842C 1500 动态规划
 */
 /*
  * dp[i]: 截止位置i能删除最多多少个数
1. 不去考虑nums[i]的删除 dp[i - 1]
2. 考虑删除nums[i], 前面相同的数为nums[j]，i - j + 1 + dp[j - 1]
整理为 i + dp[j - 1] - (j - 1)
用map去保留每一个数nums[j]对应的 dp[j - 1] - (j - 1) 最大值
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, nums[N], dp[N];

void solve() {
    dp[0] = 0;
    map<int, int> mp;
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        int num = nums[i];
        if(mp.count(num)) {
            dp[i] = max(dp[i], i + mp[num]);
            mp[num] = max(dp[i - 1] - (i - 1), mp[num]);
        } else mp[num] = dp[i - 1] - (i - 1);
    }
    cout << dp[n] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};