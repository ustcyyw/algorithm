/**
 * @Time : 2022/8/11-5:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 nums 和一个整数 k 。请你向 nums 中追加 k 个 未 出现在 nums 中的、互不相同 的 正 整数，并使结果数组的元素和 最小 。

返回追加到 nums 中的 k 个整数之和。

 

示例 1：

输入：nums = [1,4,25,10,25], k = 2
输出：5
解释：在该解法中，向数组中追加的两个互不相同且未出现的正整数是 2 和 3 。
nums 最终元素和为 1 + 4 + 25 + 10 + 25 + 2 + 3 = 70 ，这是所有情况中的最小值。
所以追加到数组中的两个整数之和是 2 + 3 = 5 ，所以返回 5 。
示例 2：

输入：nums = [5,6], k = 6
输出：25
解释：在该解法中，向数组中追加的两个互不相同且未出现的正整数是 1 、2 、3 、4 、7 和 8 。
nums 最终元素和为 5 + 6 + 1 + 2 + 3 + 4 + 7 + 8 = 36 ，这是所有情况中的最小值。
所以追加到数组中的两个整数之和是 1 + 2 + 3 + 4 + 7 + 8 = 25 ，所以返回 25 。
 

提示：

1 <= nums.length <= 105
1 <= nums[i], k <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/append-k-integers-with-minimal-sum
 */
class Solution {
public:
    /**
     * 执行用时：124 ms, 在所有 C++ 提交中击败了70.70%的用户
     * 内存消耗：64.6 MB, 在所有 C++ 提交中击败了43.72%的用户
     */
    long long minimalKSum(vector<int>& nums, int k) {
        nums.push_back(0), nums.push_back(2 * 1e9); // 加入两个哨兵
        sort(nums.begin(), nums.end());
        long long res = 0;
        for(int i = 1; i < nums.size() && k > 0; i++){
            if(nums[i] - 1 == nums[i - 1] || nums[i - 1] == nums[i]) continue;
            long long n = min(nums[i] - nums[i - 1] - 1, k);
            long long first = nums[i - 1] + 1, last = first + n - 1;
            res += n * (first + last) / 2;
            k -= n;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}