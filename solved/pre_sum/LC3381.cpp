/**
 * @Time : 2024/12/11-9:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3381 前缀和 同余
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, ll> map;
        map[0] = 0;
        ll sum = 0, res = LONG_LONG_MIN;
        for(int i = 1; i <= nums.size(); i++) {
            sum += nums[i - 1];
            int m = i % k;
            if(map.count(m)) res = max(res, sum - map[m]);
            if(map.count(m)) map[m] = min(sum, map[m]);
            else map[m] = sum;
        }
        return res;
    }
};