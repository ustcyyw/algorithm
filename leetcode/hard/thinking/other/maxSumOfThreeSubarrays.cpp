/**
 * @Time : 2022/9/18-10:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 nums 和一个整数 k ，找出三个长度为 k 、互不重叠、且全部数字和（3 * k 项）最大的子数组，并返回这三个子数组。

以下标的数组形式返回结果，数组中的每一项分别指示每个子数组的起始位置（下标从 0 开始）。如果有多个结果，返回字典序最小的一个。

 

示例 1：

输入：nums = [1,2,1,2,6,7,5,1], k = 2
输出：[0,3,5]
解释：子数组 [1, 2], [2, 6], [7, 5] 对应的起始下标为 [0, 3, 5]。
也可以取 [2, 1], 但是结果 [1, 3, 5] 在字典序上更大。
示例 2：

输入：nums = [1,2,1,2,1,2,1,2,1], k = 2
输出：[0,2,4]
 

提示：

1 <= nums.length <= 2 * 104
1 <= nums[i] < 216
1 <= k <= floor(nums.length / 3)

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-sum-of-3-non-overlapping-subarrays
 */
class Solution {
public:
    /**
     * 前缀和
     * 可以枚举中间数组的起始索引i,中间部分mid就是 nums[i, i + k]
     * 然后将原数组分为两部分，只需要分别找到前面部分left，nums[0, i - 1]
     * 和后面部分right，nums[i + k + 1, n - 1]上的长度为k最大和子数组
     * 再加上当前mid的和，就是一个可能的最大解
     * 枚举完所有中间数组的起始索引i，就能找到最终答案
     *
     * 可以预处理前面部分left上的最大和子数组及索引
     * 用left[i]表示[0,i]上最大的子数组和及其起始索引
     *
     * 注意字典序要求最小，所以对left和right的预处理有一个等号的区别。
     */
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long> sum(n + 1, 0l);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        // left [0,i]上最大的子数组和及其起始索引
        vector<vector<long>> left(n, vector(2,0l)), right(n, vector(2,0l));
        for(int i = 0; i + k - 1 < n; i++){
            long curSum = sum[i + k] - sum[i];
            if(i + k - 2 < 0 || curSum > left[i + k - 2][0])
                left[i + k - 1][0] = curSum, left[i + k - 1][1] = i;
            else
                left[i + k - 1][0] = left[i + k - 2][0], left[i + k - 1][1] = left[i + k - 2][1];
        }
        for(int i = n - 1; i - k + 1 >= 0; i--){
            long curSum = sum[i + 1] - sum[i - k + 1];
            if(i - k + 2 >= n || curSum >= right[i - k + 2][0])
                right[i - k + 1][0] = curSum, right[i - k + 1][1] = i - k + 1;
            else
                right[i - k + 1][0] = right[i - k + 2][0], right[i - k + 1][1] = right[i - k + 2][1];
        }
        vector<int> res = {-1,-1,-1};
        long max_sum = 0;
        for(int i = k; n - (i + k) >= k; i++){
            long temp = sum[i + k] - sum[i] + left[i - 1][0] + right[i + k][0];
            if(temp > max_sum){
                max_sum = temp;
                res[0] = left[i - 1][1], res[1] = i, res[2] = right[i + k][1];
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}