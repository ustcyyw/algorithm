/**
 * @Time : 2023/12/21-12:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 枚举序列中元素的数量m
 * dp[i][j][k]：截止第i个元素，一共选取了j个数，并且对m取mod的值是k的方案数
 * 最终答案 dp[n - 1][m][0]
 * 可以进行滚动优化
 */
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353, N = 101;
int n, nums[N];

long long count(int m) {
    vector<vector<long long>> dp(m + 1, vector(m, 0ll));
    dp[0][0] = 1, dp[1][nums[0] % m] = 1;
    for(int i = 1; i < n; i++) {
        int a = nums[i] % m;
        for(int j = m; j >= max(0, m - n + i + 1); j--) {
            for(int k = 0; k < m; k++) {
                if(j > 0) dp[j][k] = (dp[j][k] + dp[j - 1][(k + m - a) % m]) % mod;
            }
        }
    }
    return dp[m][0];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    long long res = 0;
    for(int i = 1; i <= n; i++)
        res += count(i);
    res %= mod;
    cout << res << endl;
}