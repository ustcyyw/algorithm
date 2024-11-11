/**
 * @Time : 2022/10/21-4:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    int maximumScore(vector<int>& nums, int k) {
        n = nums.size();
        vector<int> pre = pre_less(nums), next = next_less(nums);
        int res = 0;
        for(int i = 0; i < n; i++){
            int lo = pre[i], hi = next[i];
            if(k > lo && k < hi)
                res = max(res, (hi - lo - 1) * nums[i]);
        }
        return res;
    }

    vector<int> pre_less(vector<int>& nums){
        vector<int> res(n, -1);
        stack<int> stack;
        for(int i = 0; i < n; i++){
            while (!stack.empty() && nums[stack.top()] >= nums[i])
                stack.pop();
            if(!stack.empty()) res[i] = stack.top();
            stack.push(i);
        }
        return res;
    }

    vector<int> next_less(vector<int>& nums){
        vector<int> res(n, n);
        stack<int> stack;
        for(int i = n - 1; i >= 0; i--){
            while (!stack.empty() && nums[stack.top()] >= nums[i])
                stack.pop();
            if(!stack.empty()) res[i] = stack.top();
            stack.push(i);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}