/**
 * @Time : 2023/2/20-8:21 PM
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
     * 要让最大差值最小，要么修改最大值，要么修改最小值
     * 只要修改了其中一个值，就可以出现两个相等元素，最小差值就为0
     * 因此本题就是找修改两个值的情况下，如何让最大差值最小
     */
    int minimizeSum(vector<int>& nums) {
        int n = nums.size(), res = INT_MAX;
        sort(nums.begin(), nums.end());
        for(int i = 0, j = n - 3 + i; i <= 2; i++)
            res = min(res, nums[j] - nums[i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}