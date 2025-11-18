/**
 * @Time : 2025/11/17-10:17
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3748 2230 前缀和 二分
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        vector<ll> arr, sum = {0};
        for(int i = 0, j = 0, n = nums.size(); i < n; i = j) {
            j = i + 1;
            arr.push_back(i);
            while(j < n && nums[j] >= nums[j - 1]) j++;
            ll len = j - i;
            sum.push_back(sum.back() + len * (len + 1) / 2);
        }
        arr.push_back(nums.size());
        vector<ll> ans;
        for(auto& q : queries) {
            int l = q[0], r = q[1];
            auto it1 = --upper_bound(arr.begin(), arr.end(), l);
            auto it2 = --upper_bound(arr.begin(), arr.end(), r);
            if(it1 == it2) {
                ll len = r - l + 1;
                ans.push_back(len * (len + 1) / 2);
            } else {
                int lo = it1 - arr.begin(), hi = it2 - arr.begin();
                ll len1 = arr[lo + 1] - l, len2 = r - arr[hi] + 1;
                ans.push_back(len1 * (len1 + 1) / 2 + len2 * (len2 + 1) / 2 + sum[hi] - sum[lo + 1]);
            }
        }
        return ans;
    }
};