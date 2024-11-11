/**
 * @Time : 2022/6/30-9:25 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 一个数字的 分数 定义为数组之和 乘以 数组的长度。

比方说，[1, 2, 3, 4, 5] 的分数为 (1 + 2 + 3 + 4 + 5) * 5 = 75 。
给你一个正整数数组 nums 和一个整数 k ，请你返回 nums 中分数 严格小于 k 的 非空整数子数组数目。

子数组 是数组中的一个连续元素序列。

 

示例 1：

输入：nums = [2,1,4,3,5], k = 10
输出：6
解释：
有 6 个子数组的分数小于 10 ：
- [2] 分数为 2 * 1 = 2 。
- [1] 分数为 1 * 1 = 1 。
- [4] 分数为 4 * 1 = 4 。
- [3] 分数为 3 * 1 = 3 。
- [5] 分数为 5 * 1 = 5 。
- [2,1] 分数为 (2 + 1) * 2 = 6 。
注意，子数组 [1,4] 和 [4,3,5] 不符合要求，因为它们的分数分别为 10 和 36，但我们要求子数组的分数严格小于 10 。
示例 2：

输入：nums = [1,1,1], k = 5
输出：5
解释：
除了 [1,1,1] 以外每个子数组分数都小于 5 。
[1,1,1] 分数为 (1 + 1 + 1) * 3 = 9 ，大于 5 。
所以总共有 5 个子数组得分小于 5 。
 

提示：

1 <= nums.length <= 105
1 <= nums[i] <= 105
1 <= k <= 1015

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/count-subarrays-with-score-less-than-k
 */

class Solution {
public:
    /**
     * 数组元素都是正数，所以具有单调性，随着数组长度越长，数组的和也越大
     */
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        vector<long> sum = vector(n + 1, 0l);
        for(int i = 1; i <= n; i++)
            sum[i] += sum[i - 1] + nums[i - 1];
        long long res = 0;
        for(int i = 0; i < n; i++){
            int j = binary_search(sum, i, k);
            res += j - i + 1;
        }
        return res;
    }
    // 分数小于k的最大值的索引,返回原数组中的索引，也就是前缀和的索引-1
    int binary_search(vector<long>& sum, int start, long long k){
        int lo = start, hi = sum.size() - 1;
        while (lo < hi){
            int mid = (lo + hi + 1) >> 1;
            long long point = (sum[mid] - sum[start]) * (mid - start);
            if(point >= k) hi = mid - 1;
            else lo = mid;
        }
        return lo - 1;
    }

    /**
     * 除了使用二分，因为单调性，也可以枚举左端点的时候，去考虑右端点的最大值
     * 随着左端点的右移，原本满足条件限制的右端点，可能有进一步右移动的空间。
     * 两个指针都只会扫一次数组
     */
    long long countSubarrays2(vector<int>& nums, long long k) {
        int n = nums.size();
        vector<long> sum = vector(n + 1, 0l);
        for(int i = 1; i <= n; i++)
            sum[i] += sum[i - 1] + nums[i - 1];
        long long res = 0;
        for(int i = 0, j = 0; i < n; i++){
            while (j < n && (sum[j + 1] - sum[i]) * (j - i + 1) < k)
                j++;
            res += j - i;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}