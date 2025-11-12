/**
 * @Time : 2025/11/11-11:22
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3638 1463 单调栈 动态规划
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxBalancedShipments(vector<int>& weight) {
        int n = weight.size();
        vector<int> dp(n + 1, 0);
        stack<int> st;
        for(int i = 0; i < n; i++) {
            while(!st.empty() && weight[i] >= weight[st.top()])
                st.pop();
            if(!st.empty()) dp[i + 1] = dp[st.top()] + 1;
            st.push(i);
            dp[i + 1] = max(dp[i + 1], dp[i]);
        }
        return dp[n];
    }
};