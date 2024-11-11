/**
 * @Time : 2022/10/2-9:50 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你两个下标从 0 开始的整数数组 nums1 和 nums2 ，两个数组的大小都为 n ，同时给你一个整数 diff ，统计满足以下条件的 数对 (i, j) ：

0 <= i < j <= n - 1 且
nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff.
请你返回满足条件的 数对数目 。

 

示例 1：

输入：nums1 = [3,2,5], nums2 = [2,2,1], diff = 1
输出：3
解释：
总共有 3 个满足条件的数对：
1. i = 0, j = 1：3 - 2 <= 2 - 2 + 1 。因为 i < j 且 1 <= 1 ，这个数对满足条件。
2. i = 0, j = 2：3 - 5 <= 2 - 1 + 1 。因为 i < j 且 -2 <= 2 ，这个数对满足条件。
3. i = 1, j = 2：2 - 5 <= 2 - 1 + 1 。因为 i < j 且 -3 <= 2 ，这个数对满足条件。
所以，我们返回 3 。
示例 2：

输入：nums1 = [3,-1], nums2 = [-2,2], diff = -1
输出：0
解释：
没有满足条件的任何数对，所以我们返回 0 。
 

提示：

n == nums1.length == nums2.length
2 <= n <= 105
-104 <= nums1[i], nums2[i] <= 104
-104 <= diff <= 104

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/number-of-pairs-satisfying-inequality
 */
class Solution {
public:
    /**
     * n1[i] - n2[i] <= n1[j] - n2[j] + diff
     * 从左往右枚举j，不断计算n1[j] - n2[j]，然后找n1[j] - n2[j] + diff小于等于的i有多少
     * 单点修改，区间查询，线段树
     */
    int N = 3e4 + 10;
    vector<int> cnt = vector(8 * N, 0);
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        long long res = 0;
        for(int i = 0; i < nums1.size(); i++){
            int d = nums1[i] - nums2[i];
            res += count(1, -N, N, -N, d + diff);
            add(1, d, -N, N);
        }
        return res;
    }

    void add(int x, int pos, int l, int r){
        if(l == r) {
            cnt[x]++;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(2 * x, pos, l, mid);
        else add(2 * x + 1, pos, mid + 1, r);
        cnt[x] = cnt[2 * x] + cnt[2 * x + 1];
    }

    int count(int x, int l, int r, int L, int R){
        if(L <= l && r <= R) return cnt[x];
        int mid = (l + r) >> 1, res = 0;
        if(L <= mid) res += count(2 * x, l, mid, L, R);
        if(R > mid) res += count(2 * x + 1, mid + 1, r, L, R);
        return res;
    }
};
