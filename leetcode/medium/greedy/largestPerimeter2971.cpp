/**
 * @Time : 2023/12/26-12:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛120 t2
 */

/*
 * 枚举可能的最长边 按定义校验即可
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long largestPerimeter(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<long long> sum(n + 1, 0ll);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        for(int i = n - 1; i >= 0; i--) {
            if(sum[i] > nums[i])
                return sum[i + 1];
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}