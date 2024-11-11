/**
 * @Time : 2022/11/22-9:54 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool is_prime(char c){
        return c == '2' || c == '3' || c == '5' || c == '7';
    }
    // 某个点是切分点（子串结尾） 要求该点是非质数，且（其后一个点是质数或者它已经是最后一个点）
    bool patition(string& s, int i){
        return !is_prime(s[i]) && (i == s.size() - 1 || is_prime(s[i + 1]));
    }
    /**
     * dp[i][j]截止s[0~i]可以分成j个子串的分类方法
     * 时间复杂度 n^3 超时
     */
    int beautifulPartitions(string s, int K, int minLength) {
        int n = s.size(), mod = 1e9 + 7;
        if(K * minLength > n || !is_prime(s[0]) || is_prime(s[n - 1]))
            return 0;
        int dp[n + 1][K + 1]; memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(int i = minLength; i <= n; i++){ // 先枚举字符位置
            if (!patition(s, i - 1)) continue; // 如果该字符不能做为切分点 直接跳过
            for(int k = max(1, K - (n - i) / minLength); k <= K; k++){ // 枚举以i为切分点，能分割的子串数目k
                // [lo, i]为一个子串，枚举lo的所有可能的位置，那么lo - 1就是前置子串的末尾
                // 如果 lo - 1不是切分点，dp[lo - 1]都是0，不影响加和结果
                // [lo, i]为一个子串, 那么区间长度 i - lo + 1 >= minL, lo <= i + 1 - minLength
                // 1到lo-1要分成k-1段，区间长度 lo - 1 - 1 + 1 >= (k - 1) * minL, lo >= (k - 1) * minL + 1
                for(int lo = (k - 1) * minLength + 1; lo <= i + 1 - minLength; lo++)
                    dp[i][k] = (dp[i][k] + dp[lo - 1][k - 1]) % mod;
            }
        }
        return (int)dp[n][K];
    }

    /**
     * 方法1中 第三层循环是对连续区间（k这个维度被固定）的求和，可以进行前缀和优化
     * 且加和从 (k - 1) * minLength 加到 i - minLength
     * 需要将循环顺序进行改变
     * 先枚举分割次数k，再枚举字符位置
     * dp[k][i]定义为：截止字符s[i]，切割为k个子串的方法数
     */
    int beautifulPartitions2(string s, int K, int minLength) {
        int n = s.size(), mod = 1e9 + 7;
        if(K * minLength > n || !is_prime(s[0]) || is_prime(s[n - 1]))
            return 0;
        int dp[K + 1][n + 1]; memset(dp, 0, sizeof(dp));
        // dp的前缀和，所以长度要比n+1多1
        int sum[K + 1][n + 2]; memset(sum, 0, sizeof(sum));
        dp[0][0] = 1;
        for(int k = 1; k <= K; k++){
            // 先求k-1的前缀和
            for(int i = 1; i <= n + 1; i++)
                sum[k - 1][i] = (sum[k - 1][i - 1] + dp[k - 1][i - 1]) % mod;
            // 枚举字符位置
            for(int i = minLength; i <= n; i++){
                if (!patition(s, i - 1)) continue;
                int lo = (k - 1) * minLength, hi = i - minLength;
                // 前缀和与原数组下标有错位1，所以右端点下标要+1，左端点不变
                dp[k][i] = (sum[k - 1][hi + 1] - sum[k - 1][lo] + mod) % mod;
            }
        }
        return (int)dp[K][n];
    }
};

int main(){
    Solution s;
    cout << 0 << endl;
}