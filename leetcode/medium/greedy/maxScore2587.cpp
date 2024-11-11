/**
 * @Time : 2023/4/17-5:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxScore(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        long sum = 0;
        for(int n = nums.size(), i = n - 1; i >= 0; i--){
            sum += nums[i];
            if(sum <= 0) return n - i - 1;
        }
        return nums.size();
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}