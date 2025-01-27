/**
 * @Time : 2025/1/26-4:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3434 暴力枚举 前后缀分解
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5;
int sum[N][51];

class Solution {
public:
    /*
     * 假设将 nums[i,j]上的数字c都变为k 那么整个数组中k的数目是
     * pre[i-1] + suf[j + 1] + sum[j][c] - sum[i-1][c]
     * sum[j][c] + pre[i-1] - sum[i-1][c] + suf[j+1]
     * 要取最大值 就要使得 pre[i-1] - sum[i-1][c] 最大
     * pre和suf是指元素k的前缀和、后缀和
     *
     * 因此元素的范围是1-50很小 因此对于c这个变量 可以直接暴力枚举
     */
    int n, k;
    int maxFrequency(vector<int>& nums, int k) {
        this->n = nums.size(), this->k = k;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= 50; j++)
                sum[i][j] = sum[i - 1][j];
            sum[i][nums[i - 1]]++;
        }
        int ans = 0;
        for(int c = 1; c <= 50; c++)
            ans = max(ans, cal(c));
        return ans;
    }

    int cal(int c) {
        int ans = 0;
        for(int j = 1, pv = 0; j <= n; j++) {
            int suf = sum[n][k] - sum[j][k];
            ans = max(ans, sum[j][c] + pv + suf);
            pv = max(pv, sum[j][k] - sum[j][c]);
        }
        return ans;
    }
};
