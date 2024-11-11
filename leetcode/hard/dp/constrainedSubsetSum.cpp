/**
 * @Time : 2022/8/15-10:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 nums 和一个整数 k ，请你返回 非空 子序列元素和的最大值，子序列需要满足：子序列中每两个 相邻 的整数 nums[i] 和 nums[j] ，它们在原数组中的下标 i 和 j 满足 i < j 且 j - i <= k 。

数组的子序列定义为：将数组中的若干个数字删除（可以删除 0 个数字），剩下的数字按照原本的顺序排布。

 

示例 1：

输入：nums = [10,2,-10,5,20], k = 2
输出：37
解释：子序列为 [10, 2, 5, 20] 。
示例 2：

输入：nums = [-1,-2,-3], k = 1
输出：-1
解释：子序列必须是非空的，所以我们选择最大的数字。
示例 3：

输入：nums = [10,-2,-10,-5,20], k = 2
输出：23
解释：子序列为 [10, -2, -5, 20] 。
 

提示：

1 <= k <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/constrained-subsequence-sum
 */
class Solution {
public:
    /**
     * dp[i]表示以元素i结尾的子序列的最大值
     * dp[i] = max{dp[i-1],dp[i-2],...,dp[i-k]}
     * 转移方程中用到了一个连续区间的最大值，因此想到了单调递减的队列
     * 如果一个元素更大，并且靠右边，那么它左边更小的元素完全无用，因此队列里面的元素是单调减的
     *
     * 执行用时：224 ms, 在所有 C++ 提交中击败了69.12%的用户
     * 内存消耗：111.9 MB, 在所有 C++ 提交中击败了99.65%的用户
     */
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 1) return nums[0];
        deque<pair<int, int>> queue;
        queue.push_back(make_pair(0, nums[0]));
        for(int i = 1; i < n; i++){
            // 队列中最大的元素在k范围之外，弹出这个无效的最大元素。
            // 因为是一个位置一个位置移动，所以最多弹出一次，并且也保证队列非空
            if(queue.front().first + k < i) queue.pop_front();
            pair<int, int>& cur_max = queue.front();
            nums[i] = max(nums[i], nums[i] + cur_max.second);
            while (!queue.empty() && queue.back().second <= nums[i])
                queue.pop_back();
            queue.push_back(make_pair(i, nums[i]));
        }
        int res = nums[0];
        for(int i = 1; i < n; i++)
            res = max(res, nums[i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}