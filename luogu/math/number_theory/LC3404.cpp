/**
 * @Time : 2024/12/29-5:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3404 数学 数论 前缀和
 */
 /*
  * 观察数的值域 两个数之积最多为1e6
  * 如果枚举p和r可以确定乘积 nums[q], nums[s]是这个数的因子 并且小于1000
  * 1e6以内的数 最多有32个小于1000的因子
  * 因此可以暴力枚举小于1000的因子
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e6 + 5;

// 预处理 [1-N]范围内所有数的小于<=1000的因子
// 预处理每个数的所有因子，时间复杂度 O(MlogM)，M=1e5
// 外循环先枚举因子，内循环j代表包含该因子的数，显然是成倍增加的 j += i
vector<int> divisors[N];
int init = []() {
    for (int i = 1; i <= 1000; ++i)
        for (int j = i; j < N; j += i)
            divisors[j].push_back(i);
    return 0;
}();

class Solution {
public:
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size(), maxV = 0;
        for(int num : nums)
            maxV = max(num, maxV);
        vector<vector<int>> sum(n + 1, vector(maxV + 1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= maxV; j++)
                sum[i][j] = sum[i - 1][j];
            sum[i][nums[i - 1]]++;
        }
        ll ans = 0;
        for(int p = 1; p <= n; p++) {
            for(int r = p + 4; r + 2 <= n; r++) {
                int num = nums[p - 1] * nums[r - 1];
                for(int f : divisors[num]) {
                    if(f > maxV || num / f > maxV) continue;
                    ans += (sum[r - 2][f] - sum[p + 1][f]) * (sum[n][num / f] - sum[r + 1][num / f]);
                }
            }
        }
        return ans;
    }
};