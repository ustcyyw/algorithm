/**
 * @Time : 2025/11/10-21:33
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3738 1799 前后缀分解 枚举
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return n;
        vector<int> pre(n, 1), suf(n, 1);
        for(int i = 1; i < n; i++)
            if(nums[i] >= nums[i - 1]) pre[i] = pre[i - 1] + 1;
        for(int i = n - 2; i >= 0; i--)
            if(nums[i] <= nums[i + 1]) suf[i] = suf[i + 1] + 1;
        int len = max(1 + suf[1], 1 + pre[n - 2]);
        for(int i = 1; i < n - 1; i++) {
            if(nums[i - 1] <= nums[i + 1]) len = max(len, 1 + pre[i - 1] + suf[i + 1]);
            len = max(len, max(1 + pre[i - 1], 1 + suf[i + 1]));
        }
        return len;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}