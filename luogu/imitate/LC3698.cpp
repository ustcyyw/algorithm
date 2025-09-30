/**
 * @Time : 2025/9/29-10:04
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3698 1562 模拟 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

class Solution {
public:
    long long splitArray(vector<int>& nums) {
        int n = nums.size();
        vector<ll> sum(n + 1, 0ll);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        int j = 0;
        while(j < n - 1 && nums[j + 1] > nums[j])
            j++;
        if(j == n - 1) return abs(sum[n - 1] - nums[n - 1]);
        if(!check(nums, j + 1)) return -1;
        if(j == 0) return abs(sum[n] - nums[0] - nums[0]);
        if(nums[j] == nums[j + 1]) return abs(sum[n] - sum[j + 1] - sum[j + 1]);
        return min(abs(sum[n] - sum[j + 1] - sum[j + 1]), abs(sum[n] - sum[j] - sum[j]));
    }

    bool check(vector<int>& nums, int lo) {
        for(int j = lo; j < nums.size(); j++)
            if(nums[j] >= nums[j - 1] && j != lo)
                return false;
        return true;
    }
};