/**
 * @Time : 2022/8/11-11:23 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 执行用时：88 ms, 在所有 C++ 提交中击败了83.68%的用户
     * 内存消耗：62.1 MB, 在所有 C++ 提交中击败了12.11%的用户
     */
    int maximumTop(vector<int>& nums, int k) {
        // k > 1 留一次将可能的最大元素放回，循环结束后i指到栈顶，也就是还有一次机会能删除的元素
        int i = 0, n = nums.size();
        if(n == 1) return k % 2 == 1 ? -1 : nums[0]; // 只有一个元素，奇数次操作会让栈为空
        if(k == 1) return nums[1]; // 只能操作一次，栈顶一定是第二个元素
        int res = nums[0];
        for(; i < n && k > 1; i++, k--)
            res = max(nums[i], res);
        if(k == 1) {
            // 删除了k-1个元素，还有一次机会删除，如果再删除一次后栈顶元素nums[i + 1]更大，那应该k次全用于删除
            // 但是如果是删了k-1个元素后，栈顶的元素最大，还剩的一次操作是删除它，或者添加一个元素到栈顶，
            // 总之取不到nums[i]
            if(i + 1 < n && nums[i + 1] > res) return nums[i + 1];
        }
        // 如果还剩偶数次操作，可以在最大元素的前面（添加-删除）某个元素，让栈顶刚好剩下最大元素
        // 如果还剩奇数次操作，总是能（添加-删除）最大元素整数次，最后再把最大元素添加回去
        return res;
    }
};

int main(){
    Solution s;
    cout << 0 << endl;
}