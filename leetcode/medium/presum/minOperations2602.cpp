/**
 * @Time : 2023/3/27-2:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<long long> sum(n + 1, 0), res;
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        for(int val : queries){
            int t = lower_bound(nums.begin(), nums.end(), val) - nums.begin();
            long long v = (long long)val;
            res.push_back(v * t - sum[t] + sum[n] - sum[t] - v * (n - t));
        }
        return res;
    }

};

int main(){
    Solution s;
    vector<int> arr = {3,1,6,8}, q = {1,5};
    s.minOperations(arr, q);
    cout << 0 << endl;
}