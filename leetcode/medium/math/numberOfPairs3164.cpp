/**
 * @Time : 2024/5/27-2:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛399 t3
 */
 /*
  * 暴力 调和级数分析时间复杂度
  */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<ll, int> m1 = stastic(nums1, 1), m2 = stastic(nums2, k);
        ll ans = 0, mv = 0;
        for(int num : nums1)
            mv = max(mv, (ll)num);
        for(auto& [key, val] : m2) {
            for(ll num = key, i = 1; num * i <= mv; i++) {
                ans += (ll)val * m1[num * i];
            }
        }
        return ans;
    }

    unordered_map<ll, int> stastic(vector<int>& nums, int k) {
        unordered_map<ll, int> map;
        for(int num : nums) {
            ll key = (ll)num * k;
            map[key]++;
        }
        return map;
    }
};