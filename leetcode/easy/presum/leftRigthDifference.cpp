/**
 * @Time : 2023/2/26-9:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 给你一个下标从 0 开始的整数数组 nums ，请你找出一个下标从 0 开始的整数数组 answer ，其中：

answer.length == nums.length
answer[i] = |leftSum[i] - rightSum[i]|
其中：

leftSum[i] 是数组 nums 中下标 i 左侧元素之和。如果不存在对应的元素，leftSum[i] = 0 。
rightSum[i] 是数组 nums 中下标 i 右侧元素之和。如果不存在对应的元素，rightSum[i] = 0 。
返回数组 answer 。

 

示例 1：

输入：nums = [10,4,8,3]
输出：[15,1,11,22]
解释：数组 leftSum 为 [0,10,14,22] 且数组 rightSum 为 [15,11,3,0] 。
数组 answer 为 [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22] 。
示例 2：

输入：nums = [1]
输出：[0]
解释：数组 leftSum 为 [0] 且数组 rightSum 为 [0] 。
数组 answer 为 [|0 - 0|] = [0] 。
 

提示：

1 <= nums.length <= 1000
1 <= nums[i] <= 105

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/left-and-right-sum-differences
 */
class Solution {
public:
    vector<int> leftRigthDifference(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        vector<int> res;
        for(int i = 0, sum = 0; i < nums.size(); i++){
            sum += nums[i];
            int left = sum - nums[i], right = total - sum;
            res.push_back(abs(left - right));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}