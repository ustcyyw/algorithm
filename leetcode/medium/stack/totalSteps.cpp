/**
 * @Time : 2022/7/2-2:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 给你一个下标从 0 开始的整数数组 nums 。在一步操作中，移除所有满足 nums[i - 1] > nums[i] 的 nums[i] ，其中 0 < i < nums.length 。

重复执行步骤，直到 nums 变为 非递减 数组，返回所需执行的操作数。

 

示例 1：

输入：nums = [5,3,4,4,7,3,6,11,8,5,11]
输出：3
解释：执行下述几个步骤：
- 步骤 1 ：[5,3,4,4,7,3,6,11,8,5,11] 变为 [5,4,4,7,6,11,11]
- 步骤 2 ：[5,4,4,7,6,11,11] 变为 [5,4,7,11,11]
- 步骤 3 ：[5,4,7,11,11] 变为 [5,7,11,11]
[5,7,11,11] 是一个非递减数组，因此，返回 3 。
示例 2：

输入：nums = [4,5,7,7,13]
输出：0
解释：nums 已经是一个非递减数组，因此，返回 0 。
 

提示：

1 <= nums.length <= 105
1 <= nums[i] <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/steps-to-make-array-non-decreasing
 */
class Solution {
public:
    /**
     * nums[i] 只会被其左边更大的元素消除
     * 假设其左边第一个更大的元素是nums[j]
     * 有两种情况
     * 1.nums[j]在消除nums[i]之前没有被别的数消除
     * 2.nums[j]在消除nums[i]之前被nums[k]消除了 k < j < i, nums[k] > nums[j] > nums[i]
     * 但是对于2这种情况来说，只是j位置的数值从nums[j]变为nums[k]，要能消除到nums[i]
     * 还是同1一样，要先消除掉[j + 1, i - 1]上的所有元素
     * 那么数值为nums[j]还是nums[k]对于消除nums[i]来说等价，只要nums[k]和nums[j]都大于nums[i]
     *
     * 因此只需要找到nums[i]左边第一个大于它的数nums[j]即可
     * 然后确定区间[j + 1, i - 1]上，消除所有元素需要的最大轮次
     * 这个轮次使得nums[j]和nums[i]相邻，然后再通过一轮，就可以将nums[i]进行消除
     *
     * 设f[k]为消除nums[k]的最大轮次
     * 那么区间[j + 1, i - 1]上，消除所有元素需要的最大轮次表示为 m = max{f[j + 1], f[j + 2],...,f[i-1]}
     * 消除f[i]的最大轮次就是 m + 1
     * 另外注意，如果nums[i]的左边没有最大的数，说明没法被消除，f[i] = 0
     *
     * 接下来就是处理max{f[j + 1], f[j + 2],...,f[i-1]}
     * 在使用单调栈找nums[i]左边第一个更大的元素nums[j]时，使用的是单调递减的栈
     * 被nums[i]弹出的元素，都在[j + 1, i - 1]上，并且弹出的元素的f是已经计算过的
     * 可以记录弹出过程中的所有f中的最大值，就是[j + 1, i - 1]上的最大f
     * 因为区间[j + 1, i - 1]上不在栈中的元素，都是之前被弹出过的，并且记录过最大f，然后被更新为f+1又放回栈中
     * 也就是说栈中的元素的f，一定比不在栈中的大，那么那些元素也就无所谓了。
     *
     */
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        int res = 0, f[n];
        stack<int> stack;
        for(int i = 0; i < n; i++){
            int cur = 0; // 记录[j + 1, i - 1]上的最大f
            while(!stack.empty() && nums[stack.top()] <= nums[i]){
                cur = max(cur, f[stack.top()]);
                stack.pop();
            }
            if(!stack.empty()){ // 如果stack为空，说明当前元素是最大的，不会被消除，不必更新res
                f[i] = cur + 1; // 消除nums[i]的轮次为max{f[j + 1], f[j + 2],...,f[i-1]} + 1
                res = max(res, f[i]);
            }
            stack.push(i);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}