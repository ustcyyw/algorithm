/**
 * @Time : 2025/1/8-11:47 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3287 动态规划 位运算
 */
 /*
  * 前后两个部分的or值 再取xor 求这个最大值
  * nums[i] < 2 ^ 7 并且 nums.length <= 400
  * 前后缀分解
  * 枚举xor的值 从最大值开始往下枚举 如果能枚举到 直接返回
  *
  * 左边 left, 右边是 val ^ left
  * dp[i][j]: 截止i元素 凑出j的最少数、最多数
  * k在这之间就说明可以通过k个数得到这个结果
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 128;

class Solution {
public:
    vector<vector<int>> pre1, pre2, suf1, suf2;
    int maxValue(vector<int>& nums, int k) {
        int n = nums.size();
        pre1 = vector(n, vector(N, n + 1)), pre2 = vector(n, vector(N, - 1));
        pre1[0][0] = pre2[0][0] = 0, pre1[0][nums[0]] = pre2[0][nums[0]] = 1;
        for(int i = 1; i <= n - k - 1; i++) {
            for(int j = 0; j < N; j++)
                pre1[i][j] = pre1[i - 1][j], pre2[i][j] = pre2[i - 1][j];
            int num = nums[i];
            for(int p = 0; p < N; p++) {
                if(pre1[i - 1][p] == n + 1) continue;
                pre1[i][p | num] = min(pre1[i][p | num], pre1[i - 1][p] + 1);
                pre2[i][p | num] = max(pre2[i][p | num], pre2[i - 1][p] + 1);
            }
        }
        // 后缀的预处理
        suf1 = vector(n, vector(N, n + 1)), suf2 = vector(n, vector(N, - 1));
        suf1[n-1][0] = suf2[n-1][0] = 0, suf1[n-1][nums[n-1]] = suf2[n-1][nums[n-1]] = 1;
        for(int i = n - 2; i >= k - 1; i--) {
            for(int j = 0; j < N; j++)
                suf1[i][j] = suf1[i + 1][j], suf2[i][j] = suf2[i + 1][j];
            int num = nums[i];
            for(int p = 0; p < N; p++) {
                if(suf1[i + 1][p] == n + 1) continue;
                suf1[i][p | num] = min(suf1[i][p | num], suf1[i + 1][p] + 1);
                suf2[i][p | num] = max(suf2[i][p | num], suf2[i + 1][p] + 1);
            }
        }
        for(int i = N - 1; i >= 0; i--)
            if(check(n, k, i)) return i;
        return -1;
    }

    bool check(int n, int k, int val) {
        for(int i = k - 1; i <= n - k - 1; i++) {
            for(int j = 0; j < N; j++) {
                int t = val ^ j;
                if(pre1[i][j] <= k && pre2[i][j] >= k &&
                   suf1[i+1][t] <= k && suf2[i+1][t] >= k)
                    return true;
            }
        }
        return false;
    }
};
