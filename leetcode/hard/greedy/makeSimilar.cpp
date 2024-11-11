/**
 * @Time : 2022/10/24-8:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你两个正整数数组 nums 和 target ，两个数组长度相等。

在一次操作中，你可以选择两个 不同 的下标 i 和 j ，其中 0 <= i, j < nums.length ，并且：

令 nums[i] = nums[i] + 2 且
令 nums[j] = nums[j] - 2 。
如果两个数组中每个元素出现的频率相等，我们称两个数组是 相似 的。

请你返回将 nums 变得与 target 相似的最少操作次数。测试数据保证 nums 一定能变得与 target 相似。

 

示例 1：

输入：nums = [8,12,6], target = [2,14,10]
输出：2
解释：可以用两步操作将 nums 变得与 target 相似：
- 选择 i = 0 和 j = 2 ，nums = [10,12,4] 。
- 选择 i = 1 和 j = 2 ，nums = [10,14,2] 。
2 次操作是最少需要的操作次数。
示例 2：

输入：nums = [1,2,5], target = [4,1,3]
输出：1
解释：一步操作可以使 nums 变得与 target 相似：
- 选择 i = 1 和 j = 2 ，nums = [1,4,3] 。
示例 3：

输入：nums = [1,1,1,1,1], target = [1,1,1,1,1]
输出：0
解释：数组 nums 已经与 target 相似。
 

提示：

n == nums.length == target.length
1 <= n <= 105
1 <= nums[i], target[i] <= 106
nums 一定可以变得与 target 相似。


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-number-of-operations-to-make-arrays-imitate
 */
class Solution {
public:
    /**
     * 子问题
     * 给定两个数组a和b。每次操作可以选择两个下标i和j, i != j
     * 将a[i]+1且a[j]-1。求最少的操作次数使两个数组相似。
     * 可以证明是排序之后，对应位置的元素分别相等，能让操作次数最少
     *
     * 每次操作变为加减 k，那么只有 mod(k) 相等的数才能互相变换。
     * 因此将所有数按mod(k) 的值分成 k 组（把 x 分到第 (x % k) 组，
     * 这样每一组都变为上面的子问题，即操作意义上的相临。
     * 答案就是所有组别中对应元素的差之和，再除以(2 * k)。
     *
     * 本题中k=2，所以按奇偶性分组即可。
     */
    long long makeSimilar(vector<int>& nums, vector<int>& target) {
        vector<int> odd1, even1, odd2, even2;
        group(nums, odd1, even1);
        group(nums, odd2, even2);
        long diff = get_diff(odd1, odd2) + get_diff(even1, even2);
        return diff / 4;
    }

    long long get_diff(vector<int>& nums1, vector<int>& nums2){
        long long diff = 0;
        for(int i = 0; i < nums1.size(); i++)
            diff += abs(nums1[i] - nums2[i]);
        return diff;
    }

    void group(vector<int>& nums, vector<int>& odd, vector<int>& even){
        for(int num : nums){
            if(num % 2 == 1) odd.push_back(num);
            else even.push_back(num);
        }
        sort(odd.begin(), odd.end());
        sort(even.begin(), even.end());
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}