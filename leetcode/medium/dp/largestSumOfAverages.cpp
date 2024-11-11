/**
 * @Time : 2022/5/22-2:36 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 执行用时：16 ms, 在所有 C++ 提交中击败了80.24%的用户
     * 内存消耗：41.2 MB, 在所有 C++ 提交中击败了5.24%的用户
     *
     * 最多k组，如果组数少于k
     * 不但多个元素一组会被平均为较小的值，而且加和的数更少了，都不利于最后积分最大化
     * 因此最多k组最优的做法就是一定要划分为k组
     *
     * 为何只用枚举区间划分边界，左子区间默认为一组? 状态用一个三元组表示
     * (a, b, 2) + (b + 1, c, k - 2)
     * (a, b, 2) 的一种拆解方法是 (a, b - 1, 1) + (b, b, 1)
     * (a, b, 2) + (b + 1, c, k - 2) = (a, b - 1, 1) + (b, b, 1) + (b + 1, c, k - 2)
     * 后两项合并就是 (b, c, k - 1) 的一个子集
     *
     * 还可以拆解为 (a, b - 2, 1) + (b - 1, b, 1)
     * (a, b, 2) + (b + 1, c, k - 2) = (a, b - 2, 1) + (b - 1, b, 1) + (b + 1, c, k - 2)
     * 后两项合并就是 (b - 1, c, k - 1) 的一个子集
     *
     * 可以归纳出(a, b, 2) + (b + 1, c, k - 2)的分解方法
     * 与枚举左边界，并且左边区间仅分一个组等价
     */
    vector<vector<vector<double>>> cache;
    vector<int> preSum;
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        preSum.push_back(0);
        for(int i = 0; i < n; i++)
            preSum.push_back(preSum[i] + nums[i]);
        cache.assign(n, vector(n, vector(k + 1, 0.0)));
        return largest(nums, 0, n - 1, k);
    }

    double largest(vector<int>& nums, int lo, int hi, int k){
        if(cache[lo][hi][k] != 0.0) return cache[lo][hi][k];
        if(k == 1) { // 分成一组，直接区间和除以区间元素个数就是分数
            cache[lo][hi][k] = (preSum[hi + 1] - preSum[lo]) * 1.0 / (hi - lo + 1);
            return cache[lo][hi][k];
        }
        double res = 0.0;
        // k - 1 <= hi - mid这个条件意味着 分的组数大于元素个数，也只能每个元素一个组，再多没有意义
        for(int mid = lo; mid < hi && k - 1 <= hi - mid; mid++)
            res = max(res, largest(nums, lo, mid, 1) + largest(nums, mid + 1, hi, k - 1));
        cache[lo][hi][k] = res;
        return res;
    }
};