/**
 * @Time : 2025/11/11-09:44
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3640 2277 前后缀分解 前缀和 枚举
 */
 /*
  * [l,p],[p,q],[q,r] 每一段至少两个元素
  *
  * 枚举p，那么要求pre[p] > 1 && suf[p] > 1
  * 那么可能的l就是[p - pre[p] + 1, p - 1], 要找前缀和最小的sum[i]，这样sum[p] - sum[i]最大（[l,p]上的和）
  * q = p + suf[p] - 1, q应该满足 q < n && nums[q + 1] > nums[q]
  * 找[q + 2, r + 1]上最大的sum[j], 使得sum[j] - sum[q]最大（[q+1,r]上的和）
  * 最终答案是 sum[j] - sum[i]
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        vector<ll> sum(n + 1, 0);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        vector<int> pre(n, 1), suf(n, 1), inc_suf(n, 1);
        for(int i = 1; i < n; i++)
            if(nums[i] > nums[i - 1]) pre[i] = pre[i - 1] + 1;
        for(int i = n - 2; i >= 0; i--) {
            if(nums[i] > nums[i + 1]) suf[i] = suf[i + 1] + 1;
            if(nums[i] < nums[i + 1]) inc_suf[i] = inc_suf[i + 1] + 1;
        }
        ll ans = LONG_LONG_MIN;
        for(int p = 1; p < n - 1; p++) {
            if(suf[p] == 1 || pre[p] == 1) continue;
            int q = p + suf[p] - 1;
            if(inc_suf[q] == 1) continue;
            int lo = p - pre[p] + 1, hi = q + inc_suf[q] - 1;
            int l = findL(sum, lo, p - 1), r = findR(sum, q + 2, hi + 1);
            ans = max(ans, sum[r] - sum[l]);
        }
        return ans;
    }

    int findL(vector<ll>& sum, int lo, int hi) {
        ll idx = -1, v = LONG_LONG_MAX;
        for(int i = lo; i <= hi; i++) {
            if(sum[i] < v)
                v = sum[i], idx = i;
        }
        return (int)idx;
    }

    int findR(vector<ll>& sum, int lo, int hi) {
        ll idx = -1, v = LONG_LONG_MIN;
        for(int i = lo; i <= hi; i++) {
            if(sum[i] > v)
                v = sum[i], idx = i;
        }
        return (int)idx;
    }
};