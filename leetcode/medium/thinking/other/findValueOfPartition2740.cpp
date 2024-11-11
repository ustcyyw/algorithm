/**
 * @Time : 2023/7/19-4:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findValueOfPartition(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), res = INT_MAX;
        for(int i = 0; i < n - 1; i++)
            res = min(res, nums[i + 1] - nums[i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}