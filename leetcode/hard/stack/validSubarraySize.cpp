/**
 * @Time : 2022/7/11-7:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 nums 和一个整数 threshold 。

找到长度为 k 的 nums 子数组，满足数组中 每个 元素都 大于 threshold / k 。

请你返回满足要求的 任意 子数组的 大小 。如果没有这样的子数组，返回 -1 。

子数组 是数组中一段连续非空的元素序列。

 

示例 1：

输入：nums = [1,3,4,3,1], threshold = 6
输出：3
解释：子数组 [3,4,3] 大小为 3 ，每个元素都大于 6 / 3 = 2 。
注意这是唯一合法的子数组。
示例 2：

输入：nums = [6,5,6,5,8], threshold = 7
输出：1
解释：子数组 [8] 大小为 1 ，且 8 > 7 / 1 = 7 。所以返回 1 。
注意子数组 [6,5] 大小为 2 ，每个元素都大于 7 / 2 = 3.5 。
类似的，子数组 [6,5,6] ，[6,5,6,5] ，[6,5,6,5,8] 都是符合条件的子数组。
所以返回 2, 3, 4 和 5 都可以。
 

提示：

1 <= nums.length <= 105
1 <= nums[i], threshold <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/subarray-with-elements-greater-than-varying-threshold
 */
class Solution {
public:
    int n;
    int validSubarraySize(vector<int>& nums, int threshold) {
        n = nums.size();
        vector<int> pre = get_pre_less(nums);
        // 得到下一个更小的元素，同时检查数组是否满足题目要求
        stack<int> stack;
        for(int i = n - 1; i >= 0; i--){
            int num = nums[i];
            while (!stack.empty() && nums[stack.top()] >= num)
                stack.pop();
            // 后一个更小元素的索引 - 前一个更小元素的索引 + 1 = 以当前元素为最小值的区间的长度
            int len = (stack.empty() ? n : stack.top()) - pre[i] - 1;
            if(threshold * 1.0 / len < num)
                return len;
            stack.push(i);
        }
        return -1;
    }

    // 得到前一个更小元素的索引
    vector<int> get_pre_less(vector<int>& nums){
        vector<int> pre = vector(n, -1);
        stack<int> stack;
        for(int i = 0; i < n; i++){
            int num = nums[i];
            while (!stack.empty() && nums[stack.top()] >= num)
                stack.pop();
            if(!stack.empty()) pre[i] = stack.top();
            stack.push(i);
        }
        return pre;
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,3,4,3,1};
    s.validSubarraySize(arr, 6);
    cout << 0 << endl;
}