/**
 * @Time : 2025/1/22-10:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3333 动态规划 正难则反 前缀和优化
 */
 /*
  * 连续相同的字母 至少选择1个 最多则全选
  * 所有总的可能选择方式就是 c1 * c2 * ... cm
  * 如果m >= k，那么所有可能的选择字符串长度都 >= k 直接返回这个结果就好
  *
  * 否则就计算一下字符串长度 < k一共有多少可能 用总的减去这个值即可（正难则反）
  * dp[i][j]: 截止第i个字母 长度为k的方案数
  * 当前字符可以选择 1～ci 个
  * 如果当前选1个 前面就需要j-1个
  * 如果当前选2个 前面就需要j-2个
  * 显然需要前缀和优化 sum[i][j]: 截止第i个字母 长度<=k的方案数之和
  * 由于 m < k 的前提下才需要计算 因此整体的时间复杂度是 k^2
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    int possibleStringCount(string word, int k) {
        vector<int> arr;
        for(int i = 0, j, n = word.size(); i < n; i = j) {
            j = i + 1;
            while(j < n && word[j] == word[i])
                j++;
            arr.push_back(j - i);
        }
        ll base = 1;
        for(int num : arr)
            base = base * num % mod;
        if(arr.size() >= k) return base;
        return (base - cal(arr, k) + mod) % mod;
    }

    ll cal(vector<int>& arr, int k) {
        int n = arr.size();
        // dp[i][j]: 截止第i个字母 长度为k的方案数
        vector<vector<ll>> dp(n, vector(k, 0ll));
        // sum[i][j]: 截止第i个字母 长度<=k的方案数之和
        vector<vector<ll>> sum(n, vector(k, 0ll));
        for(int j = 1; j < k; j++)
            sum[0][j] = sum[0][j - 1] + (j <= arr[0]);
        for(int i = 1; i < n; i++) {
            int num = arr[i]; // 当前字母可以拿1或者num个
            for(int j = i + 1; j < k; j++) {
                int hi = j - 1, lo = max(j - num, i);
                dp[i][j] = (sum[i - 1][hi] - sum[i - 1][lo - 1] + mod) % mod;
                sum[i][j] = (sum[i][j - 1] + dp[i][j]) % mod;
            }
        }
        return sum[n - 1][k - 1];
    }
};
