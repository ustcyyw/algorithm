/**
 * @Time : 2022/8/15-11:50 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 nums 和一个正整数 threshold  ，你需要选择一个正整数作为除数，然后将数组里每个数都除以它，并对除法结果求和。

请你找出能够使上述结果小于等于阈值 threshold 的除数中 最小 的那个。

每个数除以除数后都向上取整，比方说 7/3 = 3 ， 10/2 = 5 。

题目保证一定有解。

 

示例 1：

输入：nums = [1,2,5,9], threshold = 6
输出：5
解释：如果除数为 1 ，我们可以得到和为 17 （1+2+5+9）。
如果除数为 4 ，我们可以得到和为 7 (1+1+2+3) 。如果除数为 5 ，和为 5 (1+1+1+2)。
示例 2：

输入：nums = [2,3,5,7,11], threshold = 11
输出：3
示例 3：

输入：nums = [19], threshold = 5
输出：4
 

提示：

1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 10^6
nums.length <= threshold <= 10^6

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-the-smallest-divisor-given-a-threshold
 */
class Solution {
public:
    /**
     * 当前尝试的数太小，和就会超过threshold，那么数就需要增大
     * 当前尝试的数让和不超过threshold，那么当前数是一个可选的答案，要去尝试更小的数
     *
     * 执行用时：32 ms, 在所有 C++ 提交中击败了73.24%的用户
     * 内存消耗：21.6 MB, 在所有 C++ 提交中击败了85.74%的用户
     */
    int smallestDivisor(vector<int>& nums, int threshold) {
        int lo = 1, hi = 1e6;
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(check(nums, mid, threshold)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool check(vector<int>& nums, int k, int t){
        long sum = 0;
        for(int num : nums)
            sum += num % k == 0 ? num / k : num / k + 1;
        return sum <= t;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}