/**
 * @Time : 2024/4/14-4:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛393 t4
 */
 /*
  * 明显的划分型dp
  * dp[i][j]:以i元素为结尾并且这是第j个子数组的最小值
  * dp[i][j] = min{dp[k - 1][j - 1] + nums[i]}, for all k such ans[k, i] = vals[j]
  * 但是每次枚举k会超时 可以考虑and操作的单调性
  * and操作只会单调递减，因此满足and操作结果为vals[j]的k 如果存在 一定在一个连续区间上
  * 那么确定了区间的情况下，假定区间是[lo, hi]，那么前一个子数组的结尾索引就在区间[lo - 1, hi - 1]
  * dp[i][j] = min{dp[lo-1, hi - 1][j - 1]} 是一个区间最小值问题 可以使用线段树维护
  * 而且要分多少个组就得维护多少个线段树
  *
  * 剩下的关键就是确定lo和hi 依然是考虑and操作的单调性
  * 记target = vals[j] [mid, i]上and的结果是num
  * 如果 num > target 就说明k应该小于mid
  * 如果 num < target 说明k应该大于mid
  * 这是大致的二分思路。
  * 具体而言 要找到 最小的k使得 num >= target 这就是k的左端点lo
  * 还要找到最大的k使得 num <= target 这就是k的右端点hi
  * k的取值范围为[1, i]，另外找到lo和hi后还要注意 [lo, i], [hi, i]上and的结果是否真的等于target
  *
  * 如何快速计算num，可以通过前缀和记录区间上某个数位是否出现了0
  * 如果出现了0，该位就是0，其它位则是1 同过位运算计算num
  */
#include<bits/stdc++.h>
using namespace std;

const int MAX_VAL = 1e9;
#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val; // 存储区域上的最小值

    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = min(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = MAX_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MAX_VAL);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

class Solution {
public:
    vector<vector<int>> zSum;
    int minimumValueSum(vector<int>& nums, vector<int>& vals) {
        int n = nums.size(), m = vals.size();
        zSum.assign(n + 1, vector(18, 0));
        for(int i = 1; i <= n; i++) {
            int num = nums[i - 1];
            for(int j = 0; j < 18; j++) {
                zSum[i][j] = zSum[i - 1][j];
                if(((1 << j) & num) == 0)
                    zSum[i][j]++;
            }
        }
        vector<SegmentTree> trees(m + 1, SegmentTree(n + 1));
        vector<vector<int>> dp(n + 1, vector(m + 1, MAX_VAL));
        dp[0][0] = 0, trees[0].add(0, 0);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= min(m, i); j++) {
                int val = vals[j - 1];
                int lo = leftB(i, val), hi = rightB(i, val);
                if(lo > hi || get_num(lo, i) != val || get_num(hi, i) != val) continue;
                // and操作等于val的左端点（当前组左端点）是[lo, hi]，那么上一个组的右端点就是[lo - 1, hi - 1]
                dp[i][j] = trees[j - 1].search(lo - 1, hi - 1) + nums[i - 1];
                trees[j].add(i, dp[i][j]);
            }
        }
        return dp[n][m] >= MAX_VAL ? -1 : dp[n][m];
    }

    int get_num(int lo, int hi) {
        int res = (1 << 18) - 1;
        for(int j = 0; j < 18; j++) {
            if(zSum[hi][j] - zSum[lo - 1][j])
                res ^= (1 << j);
        }
        return res;
    }
    // 找and操作结果num >= target的最小值
    int leftB(int i, int target) {
        int lo = 1, hi = i;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            int num = get_num(mid, i);
            if(num >= target) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
    // 找and操作sum <= target的最大值
    int rightB(int i, int target) {
        int lo = 1, hi = i;
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            int num = get_num(mid, i);
            if(num <= target) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
};