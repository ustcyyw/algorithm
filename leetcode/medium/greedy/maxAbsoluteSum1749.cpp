/**
 * @Time : 2022/12/5-9:39 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int res = maxSum(nums);
        for(int i = 0; i < nums.size(); i++)
            nums[i] = -nums[i];
        return max(res, maxSum(nums));
    }

    int maxSum(vector<int>& nums){
        int res = 0;
        for(int i = 0, sum = 0; i < nums.size(); i++){
            if(sum >= 0) sum += nums[i];
            else sum = nums[i];
            res = max(res, sum);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}