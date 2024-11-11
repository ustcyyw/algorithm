/**
 * @Time : 2023/2/19-5:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/**
 * 给你一个下标从 0 开始的整数数组 nums 。

如果存在一些整数满足 0 <= index1 < index2 < ... < indexk < nums.length ，得到 nums[index1] | nums[index2] | ... | nums[indexk] = x ，那么我们说 x 是 可表达的 。换言之，如果一个整数能由 nums 的某个子序列的或运算得到，那么它就是可表达的。

请你返回 nums 不可表达的 最小非零整数 。

 

示例 1：

输入：nums = [2,1]
输出：4
解释：1 和 2 已经在数组中，因为 nums[0] | nums[1] = 2 | 1 = 3 ，所以 3 是可表达的。由于 4 是不可表达的，所以我们返回 4 。
示例 2：

输入：nums = [5,3,2]
输出：1
解释：1 是最小不可表达的数字。
 

提示：

1 <= nums.length <= 105
1 <= nums[i] <= 109


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-impossible-or
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 1: 0, 2: 10, 4: 100, 8:1000
     * 用1和2可以得到 1-3的所有数
     * 用1和2和4可以得到1-7的所有数
     * 用1和2和4和8可以得到1-15的所有数
     *
     * 找到了1，下一个可能无法表示的数就是2
     * 去找2是否存在
     *
     * 找到了1和2 那么下一个可能无法表示的数就是4
     * 去看4是否在，如果4找到了，那么1-7的数都可以表示
     * 下一个可能无法表示的数就是8
     * 去找8是否存在，如果8找到了，1-15的数都可以表示
     * 下一个可能无法表示的数就是16
     *
     * 因此只要去找2的幂次是否存在即可
     */
    int minImpossibleOR(vector<int>& nums) {
        unordered_set<int> set;
        for(int num : nums) set.insert(num);
        int t = 1;
        while (set.count(t)) t *= 2;
        return t;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}