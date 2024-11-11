/**
 * @Time : 2023/3/2-10:53 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
//    int triangularSum(vector<int>& nums) {
//        return sum(nums);
//    }
//
//    int sum(vector<int>& nums){
//        int n = nums.size();
//        if(n == 1) return nums[0];
//        vector<int> arr;
//        for(int i = 0; i < n - 1; i++)
//            arr.push_back((nums[i] + nums[i + 1]) % 10);
//        return sum(arr);
//    }

    int triangularSum(vector<int>& nums) {
        for(int n = nums.size(); n > 1; n--){
            for(int i = 0; i < n - 1; i++)
                nums[i] = (nums[i] + nums[i + 1]) % 10;
        }
        return nums[0];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}