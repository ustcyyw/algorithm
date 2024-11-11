/**
 * @Time : 2022/10/17-9:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个二进制数组 nums 和一个整数 k 。

k位翻转 就是从 nums 中选择一个长度为 k 的 子数组 ，同时把子数组中的每一个 0 都改成 1 ，把子数组中的每一个 1 都改成 0 。

返回数组中不存在 0 所需的最小 k位翻转 次数。如果不可能，则返回 -1 。

子数组 是数组的 连续 部分。

 

示例 1：

输入：nums = [0,1,0], K = 1
输出：2
解释：先翻转 A[0]，然后翻转 A[2]。
示例 2：

输入：nums = [1,1,0], K = 2
输出：-1
解释：无论我们怎样翻转大小为 2 的子数组，我们都不能使数组变为 [1,1,1]。
示例 3：

输入：nums = [0,0,0,1,0,1,1,0], K = 3
输出：3
解释：
翻转 A[0],A[1],A[2]: A变成 [1,1,1,1,0,1,1,0]
翻转 A[4],A[5],A[6]: A变成 [1,1,1,1,1,0,0,0]
翻转 A[5],A[6],A[7]: A变成 [1,1,1,1,1,1,1,1]
 

提示：

1 <= nums.length <= 105
1 <= k <= nums.length

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-number-of-k-consecutive-bit-flips
 */
class Solution {
public:
    /**
     * 关键1：遇到0，应该从当前位置起的k个元素翻转。
     * 如果取之前的元素参与翻转，前面转为1的元素又变为0，一通操作白忙活
     *
     * 关键2：翻转的范围是[i, i + k - 1]，这一个区间上的所有元素的翻转操作都+1
     * 就需要使用差分与前缀和去记录到某个元素时，该元素被翻转了多少次
     */
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size(), res = 0;
        vector<int> diff(n + 1, 0);
        for(int i = 0, sum = 0; i < n; i++){
            sum += diff[i];
            if((sum + nums[i]) % 2 == 1) continue; // 当前元素是1
            if(i + k - 1 < n) { // 翻转
                res++;
                sum++; // [i, i + k - 1]被翻转一次，那么diff[i]++, sum也需要+1
                diff[i + k]--;
            } else return -1;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}