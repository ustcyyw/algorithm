/**
 * @Time : 2023/12/22-4:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * s[l,r]: 表示字符串区间[l,r]上对应的数字
 * dp[i]： 是[0,i]上所有拆分之和
 * 最后一个数字的右边界是i，枚举最后一个数字的左边界可得dp[i]的转移方程
 *
 * dp[i] = dp[i-1] * s[i] + dp[i-2] * s[i-1,i] + ... dp[0] * s[1,i] + s[0,i]
 * 要通过枚举计算dp[i]，会tle，下标的形式是连续的 看看dp[i-1]
 * dp[i-1] = dp[i-2] * s[i-1] + dp[i-3] * s[i-2,i-1] + ... dp[0] * s[1,i-1] + s[0,i-1]
 *
 * dp[i]和dp[i-1]似乎有交叉项 dp[i-2]、dp[i-3]、...、dp[0]
 * 但系数不同 dp[i]中有一项 dp[i-2] * s[i-1,i]， dp[i-1]对应的是 dp[i-2] * s[i-1]
 * 系数存在关系 s[i-1,i] = s[i-1] * 10 + s[i]
 * 因此，进行变换
 * dp[i-1] * 10 + (dp[i-2] + dp[i-3] + ... dp[0] + 1) * s[i]
 * = dp[i-2] * s[i-1] * 10 + dp[i-2] * s[i]
 * + dp[i-3] * s[i-2,i-1] * 10 + dp[i-3] * s[i]
 * + ...
 * + dp[0] * s[1,i-1] * 10 + dp[0] * s[i]
 * + s[0,i-1] * 10 + s[i]
 *
 * = dp[i-2] * (s[i-1] * 10 + s[i]) + dp[i-3] * (s[i-2,i-1] * 10 + s[i]) + ...
 * + dp[0] * (s[1,i-1] * 10 + s[i]) + s[0,i]
 *
 * = dp[i-2] * s[i-1,i] + dp[i-3] * s[i-2,i] + ... + dp[0] * s[1,i] + s[0,i]
 *
 * 因此
 * dp[i-1] * s[i] + dp[i-1] * 10 + (dp[i-2] + dp[i-3] + ... dp[0] + 1) * s[i]
 * = dp[i-1] * s[i] + dp[i-2] * s[i-1,i] + dp[i-3] * s[i-2,i] + ... + dp[0] * s[1,i] + s[0,i]
 * = dp[i]
 *
 * 整理得
 * dp[i] = dp[i-1] * (10 + s[i]) + (sum[i-2] + 1) * s[i]
 * 其中 sum[j] 表示 dp序列的前缀和
 *
 * 再以case为例子 计算一遍 对于输入5915
 * 前两项是边界条件特殊计算，dp[0] = 5， dp[1] = 5 * 9 + 59 = 104
 * dp[2] = dp[1] * 11 + (sum[0] + 1) * 1 = 104 * 11 + 6 = 1150
 * dp[3] = 1150 * 15 + (104 + 5 + 1) * 5 = 17800
 */

#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n;
string s;

long long solve() {
    if(n == 1) return s[0] - '0';
    vector<long long> dp(n);
    dp[0] = s[0] - '0', dp[1] = dp[0] * (s[1] - '0') + dp[0] * 10 + (s[1] - '0');
    if(n == 2) return dp[1];
    vector<long long> sum(n);
    sum[0] = dp[0], sum[1] = dp[0] + dp[1];
    for(int i = 2; i < n; i++) {
        int c = s[i] - '0';
        dp[i] = (dp[i-1] * (10 + c) + (sum[i-2] + 1) * c) % mod;
        sum[i] = (sum[i - 1] +  dp[i]) % mod;
    }
    return dp[n - 1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n; cin >> s;
    cout << solve() << endl;
}