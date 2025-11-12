/**
 * @Time : 2025/1/6-12:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3410 数据结构 线段树 维护区间上非空子数组最大和
 */
 /*
  * 注意特判都是负数的情况即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e6 + 5;
#define ls x << 1
#define rs (x << 1) | 1

class Solution {
public:
    vector<ll> sum, sumL, sumR, ms;
    long long maxSubarraySum(vector<int>& nums) {
        int n = nums.size(), maxV = INT_MIN;
        sum.assign(n * 4, 0ll), sumL.assign(n * 4, 0ll);
        sumR.assign(n * 4, 0ll), ms.assign(n * 4, 0ll);
        unordered_map<int, vector<int>> map;
        for(int i = 0; i < n; i++) {
            add(1, 0, n - 1, i, nums[i]);
            if(nums[i] < 0) map[nums[i]].push_back(i);
            maxV = max(maxV, nums[i]);
        }
        if(maxV <= 0) return maxV;
        ll ans = search(1, 0, n - 1, 0, n - 1)[3];
        for(auto& [k, arr] : map) {
            for(int idx : arr)
                add(1, 0, n - 1, idx, 0);
            ans = max(ans, search(1, 0, n - 1, 0, n - 1)[3]);
            for(int idx : arr)
                add(1, 0, n - 1, idx, k);
        }
        return ans;
    }

    void update(int x) {
        sum[x] = sum[ls] + sum[rs];
        // 如果最大子数组和没有跨mid max(ms[ls], ms[rs]); 最大子数组和跨越了mid sumL[rs] + sumR[ls]
        ms[x] = max({ms[ls], ms[rs], max(sumL[rs], 0ll) + sumR[ls], sumL[rs] + max(0ll, sumR[ls])});
        sumR[x] = max(sumR[rs], sum[rs] + max(0ll, sumR[ls]));
        sumL[x] = max(sumL[ls], sum[ls] + max(0ll, sumL[rs]));
    }

    void add(int x, int l, int r, int pos, int v) {
        if(l == r) { // 单点修改 不是单点加减
            sum[x] = sumL[x] = sumR[x] = v, ms[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        update(x);
    }

    vector<ll> search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return {sum[x], sumL[x], sumR[x], ms[x]};
        int mid = (l + r) >> 1;
        vector<ll> res(4, LONG_LONG_MIN);
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) {
            if(res[0] != LONG_LONG_MIN) {
                vector<ll> aux(4, 0), rt = search(rs, mid + 1, r, a, b);
                aux[0] = res[0] + rt[0];
                // sumL[x] = max(sumL[ls], sum[ls] + max(0, sumL[rs]));
                aux[1] = max(res[1], res[0] + max(0ll, rt[1]));
                // sumR[x] = max(sumR[rs], sum[rs] + max(0, sumR[ls]));
                aux[2] = max(rt[2], rt[0] + max(0ll, res[2]));
                aux[3] = max({res[3], rt[3],
                              max(rt[1], 0ll) + res[2], rt[1] + max(0ll, res[2])});
                swap(res, aux);
            } else res = search(rs, mid + 1, r, a, b);
        }
        return res;
    }
};