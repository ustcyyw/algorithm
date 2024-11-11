/**
 * @Time : 2022/9/18-3:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个长度为 n 下标从 0 开始的数组 nums ，数组中所有数字均为非负整数。对于 0 到 n - 1 之间的每一个下标 i ，你需要找出 nums 中一个 最小 非空子数组，它的起始位置为 i （包含这个位置），同时有 最大 的 按位或运算值 。

换言之，令 Bij 表示子数组 nums[i...j] 的按位或运算的结果，你需要找到一个起始位置为 i 的最小子数组，这个子数组的按位或运算的结果等于 max(Bik) ，其中 i <= k <= n - 1 。
一个数组的按位或运算值是这个数组里所有数字按位或运算的结果。

请你返回一个大小为 n 的整数数组 answer，其中 answer[i]是开始位置为 i ，按位或运算结果最大，且 最短 子数组的长度。

子数组 是数组里一段连续非空元素组成的序列。

 

示例 1：

输入：nums = [1,0,2,1,3]
输出：[3,3,2,2,1]
解释：
任何位置开始，最大按位或运算的结果都是 3 。
- 下标 0 处，能得到结果 3 的最短子数组是 [1,0,2] 。
- 下标 1 处，能得到结果 3 的最短子数组是 [0,2,1] 。
- 下标 2 处，能得到结果 3 的最短子数组是 [2,1] 。
- 下标 3 处，能得到结果 3 的最短子数组是 [1,3] 。
- 下标 4 处，能得到结果 3 的最短子数组是 [3] 。
所以我们返回 [3,3,2,2,1] 。
示例 2：

输入：nums = [1,2]
输出：[2,1]
解释：
下标 0 处，能得到最大按位或运算值的最短子数组长度为 2 。
下标 1 处，能得到最大按位或运算值的最短子数组长度为 1 。
所以我们返回 [2,1] 。
 

提示：

n == nums.length
1 <= n <= 105
0 <= nums[i] <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/smallest-subarrays-with-maximum-bitwise-or
 */
class Solution {
public:
    /**
     * 位或，只要在[i, n - 1]上有一个数字中的某一位出现了1
     * 那最大位或值中一定要有这一位
     * 又要要求子数组长度最短，所以要找到右边该位出现了1的数字的最小索引
     * 所有出现1的二进制位 都找到最小索引，
     * 再取最小索引的最大值，就能涵盖所有二进制位的1，取得最大位或值，并且子数组长度最小
     */
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size(), r = 32;
        vector<int> res(n, 0), indexs(r, -1);
        for(int i = n - 1; i >= 0; i--){
            int num = nums[i], hi = i;
            for(int j = 0; j < r; j++){
                if((1 << j) & num) indexs[j] = i;
                hi = max(hi, indexs[j]);
            }
            res[i] = hi - i + 1;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}