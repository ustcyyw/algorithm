/**
 * @Time : 2025/9/30-15:46
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3679 1578 模拟 滑动窗口
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minArrivalsToDiscard(vector<int>& nums, int w, int m) {
        vector<int> cnt(1e5 + 2, 0);
        int ans = 0;
        for(int n = nums.size(), lo = 0, hi = 0; hi < n; hi++) {
            int num = nums[hi];
            if(hi - lo + 1 > w) {
                if(nums[lo] != -1) cnt[nums[lo]]--;
                lo++;
            }
            if(cnt[num] == m) ans++, nums[hi] = -1;
            else cnt[num]++;
        }
        return ans;
    }
};