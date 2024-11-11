/**
 * @Time : 2022/9/2-1:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 nums 。「数组值」定义为所有满足 0 <= i < nums.length-1 的 |nums[i]-nums[i+1]| 的和。

你可以选择给定数组的任意子数组，并将该子数组翻转。但你只能执行这个操作 一次 。

请你找到可行的最大 数组值 。

 

示例 1：

输入：nums = [2,3,1,5,4]
输出：10
解释：通过翻转子数组 [3,1,5] ，数组变成 [2,5,1,3,4] ，数组值为 10 。
示例 2：

输入：nums = [2,4,9,24,2,1,10]
输出：68
 

提示：

1 <= nums.length <= 3*10^4
-10^5 <= nums[i] <= 10^5


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/reverse-subarray-to-maximize-array-value
 */
class Solution {
public:
    /**
     * 比较显然的一个点在于翻转子数组，子数组内部贡献的值不变，
     * 只有两个边界左右两边的点，一共四个，会造成值的变化。
     * 那么我们找这个变化值的最大值即可，假定原数组的值为base
     * res = max(change_val) + base
     *
     * 比如选取的要翻转的子数组是[i,j]，左边界的前一个元素是i-1，右边界的后一个元素是j+1
     * x x x , nums[i - 1], nums[i], x x x , nums[j], nums[j + 1], x x x
     * （这其实就要求i > 0, j < n - 1）
     * 从左往右这四个元素的值分别是 a b c d
     *
     * 那么 change_val = -|c-d| - |b-a| + |d-b| + |c-a|
     * 关于abcd的大小关系，4的全排列，一共24种
     *
     * 大小顺序
     * a b c d, change_val = 2b - 2c
     * b a c d, change_val = 2a - 2c
     * a b d c, change_val = 2b - 2d
     * d c b a, change_val = 2c - 2b
     * b a d c, change_val = 2a - 2d
     * b c a d, change_val = 0
     * ....
     * 可以发现
     * a和b总是只出现一个，c和d也总是只出现一个，相邻的一对元素只有一个元素参与计算
     * 或者change_val直接是0，这种情况下交换后的数组值是base
     *
     * 当change_val不为0时，change_val的值总是相邻元素中小的那个-另一对相邻元素中较大的那个，将这个差*2
     * 因此我们找相邻元素对中较小元素的最大值
     * 和相邻元素对中较大元素的最小值
     * 就能让change_val最大
     */
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return 0;
        int base = 0l;
        for(int i = 1; i < n; i++)
            base += abs(nums[i] - nums[i - 1]);
        int res = base;
        // 固定要翻转的子数组第一个元素为nums[0]（或者最后一个元素为nums[n - 1]）
        // 是特殊情况，分别先进行枚举右（左）边界求解
        for(int i = 2; i < n; i++)
            res = max(res, base - abs(nums[i] - nums[i - 1]) + abs(nums[i] - nums[0]));
        for(int i = 0; i < n - 2; i++)
            res = max(res, base - abs(nums[i] - nums[i + 1]) + abs(nums[i] - nums[n - 1]));
        // 子数组左右边界都不是原数组边界的情况
        // 找pair中较小元素的最大值，较大元素的最小值
        int pair_max = min(nums[0], nums[1]), pair_min = max(nums[0], nums[1]);
        for(int i = 0; i < n - 1; i++){
            int less = min(nums[i], nums[i + 1]), more = max(nums[i], nums[i + 1]);
            pair_max = max(pair_max, less);
            pair_min = min(pair_min, more);
        }
        return max(res, (pair_max - pair_min) * 2);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}