/**
 * @Time : 2024/9/11-3:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3282 贪心 单调栈
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 贪心 找下一个更大值
     */
    long long findMaximumScore(vector<int>& nums) {
        int n = nums.size();
        stack<int> stack;
        vector<int> next(n, n - 1);
        for(int i = n - 1; i >= 0; i--) {
            while(!stack.empty() && nums[stack.top()] <= nums[i])
                stack.pop();
            if(!stack.empty()) next[i] = stack.top();
            stack.push(i);
        }
        long long res = 0;
        for(int i = 0; i < n - 1; ) {
            int j = next[i];
            res +=  (long long)nums[i] * (j - i);
            i = j;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}