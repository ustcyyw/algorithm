/**
 * @Time : 2023/2/12-4:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    /*
     * 二分
     * nums[i] + nums[j] <= upper
     * nums[i] <= upper - nums[j]
     * 找到最大的 i 满足 nums[i] > upper - nums[i]
     * 那么 nums[i - 1] + nums[i] <= upper了
     *
     * nums[i] + nums[j] >= lower
     * nums[i] >= lower - nums[j]，找满足条件的j的最小值
     */
    long long countFairPairs(vector<int> &nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        long long res = 0;
        for(int j = 0; j < nums.size(); j++){
            int num = nums[j];
            auto r = upper_bound(nums.begin(), nums.begin() + j, upper - nums[j]);
            auto l = lower_bound(nums.begin(), nums.begin() + j, lower - nums[j]);
            res += r - l;
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> arr = {1,7,9,2,5};
    cout << 0 << endl;
}