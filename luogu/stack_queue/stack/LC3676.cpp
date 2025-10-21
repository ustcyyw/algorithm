/**
 * @Time : 2025/10/20-23:15
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 如果取nums[l]为较小的值，nums[r] >= nums[l]，且中间的数 < nums[l]
     * 找下一个 >= nums[l]的元素 (单调栈) 这样就能构成一个满足要求的数组了
     * 对于 j > r 的右边界，由于存在了 nums[r] >= nums[l]，所以一定找不到满足条件的数组了
     */
    long long bowlSubarrays(vector<int>& nums) {
        int ans = 0, n = nums.size();
        stack<int> st1, st2;
        for(int i = 0; i < n; i++) {
            while(!st1.empty() && nums[st1.top()] < nums[i])
                st1.pop();
            if(!st1.empty() && i - st1.top() + 1 >= 3) ans++;
            st1.push(i);
        }
        for(int i = n - 1; i >= 0; i--) {
            while(!st2.empty() && nums[st2.top()] <= nums[i])
                st2.pop();
            if(!st2.empty() && st2.top() - i + 1 >= 3) ans++;
            st2.push(i);
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}