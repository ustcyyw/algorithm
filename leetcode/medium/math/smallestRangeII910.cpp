/**
 * @Time : 2022/12/29-10:09 AM
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
     * 数组中的每个数，增加或者减少k
     * 要让绝对值之差更小，就要尽可能的让每一个数尽量落到某个集中的区域
     * 也就是大的数减小，小的数变大
     * 假设两个数a和b，a < b，且b现在加上k
     * 就这两个数来讲，此时a如果减少k，差值增大。
     * 也就是说如果某个数增大k，那么比它小的数也应该增大k。
     * 比它大的数无法确定，但是如果c > b，也将c增大k，这种情况等价于c增大k时，将所有小于c的数也增大k的情况
     * 因此可以枚举增大k的临界数字，小于这个数字的统一增大k，大于这个数字的统一减小k
     * 需要将数组排序
     * nums[i]为临界数字时，
     * 最小值为min(nums[0] + k, nums[i + 1] - k)
     * 最大值为max(nums[i] + k, nums[n - 1] - k)
     *
     * 注意 也可能是所有数统一增加k或者减少k，这种情况的分数就是nums[n - 1] - nums[0]
     */
    int smallestRangeII(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), res = nums[n - 1] - nums[0];
        for(int i = 0; i < n - 1; i++){
            int min_val = min(nums[0] + k, nums[i + 1] - k);
            int max_val = max(nums[i] + k, nums[n - 1] - k);
            res = min(res, max_val - min_val);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}