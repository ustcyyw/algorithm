/**
 * @Time : 2023/2/11-8:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDifference(vector<int>& nums) {
        if(nums.size() <= 3) return 0;
        sort(nums.begin(), nums.end());
        int res = INT_MAX, n = nums.size();
        for(int i = 3, j = n - 1; i >= 0; i--, j--)
            res = min(res, nums[j] - nums[i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}