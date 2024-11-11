/**
 * @Time : 2022/9/3-2:36 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。

请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
 

示例 1：

输入：nums = [1,2,0]
输出：3
示例 2：

输入：nums = [3,4,-1,1]
输出：2
示例 3：

输入：nums = [7,8,9,11,12]
输出：1
 

提示：

1 <= nums.length <= 5 * 105
-231 <= nums[i] <= 231 - 1


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/first-missing-positive
 */
class Solution {
public:
    /**
     * 执行用时：40 ms, 在所有 C++ 提交中击败了90.74%的用户
     * 内存消耗：30.6 MB, 在所有 C++ 提交中击败了88.88%的用户
     */
    int firstMissingPositive(vector<int>& nums) {
        if(!has_one(nums)) return 1;
        int n = nums.size();
        for(int i = 0; i < n; i++){
            long pos = (long)nums[i] - 1; // 比如1要放在位置0
            while (pos >= 0 && pos < n && pos != (long)nums[pos] - 1){
                long next = (long)nums[pos] - 1;
                nums[pos] = pos + 1;
                pos = next;
            }
        }
        for(int i = 0; i < n; i++)
            if(nums[i] != i + 1)
                return i + 1;
        return n + 1;
    }

    bool has_one(vector<int>& nums){
        for(int num : nums){
            if(num == 1) {
                return true;
            }
        }
        return false;
    }
};

int main(){
    Solution s;
    vector<int> arr = {3,4,-1,1};
    s.firstMissingPositive(arr);
    cout << 0 << endl;
}