/**
 * @Time : 2023/11/26-6:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛118 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // dp[i]: 购买了水果i并且没有遗漏的最小花费
//    int minimumCoins(vector<int>& prices) {
//        int n = prices.size(), res = INT_MAX;
//        vector<int> dp(n + 1, INT_MAX);
//        dp[0] = 0;
//        for(int i = 1; i <= n; i++) {
//            for(int j = i - 1; j >= 0 && j + j >= i - 1; j--)
//                dp[i] = min(dp[i], dp[j]);
//            dp[i] += prices[i - 1];
//            if(i + i >= n) res = min(res, dp[i]);
//        }
//        return res;
//    }

    // 可以单调队列优化
    int minimumCoins(vector<int>& prices) {
        int n = prices.size(), res = INT_MAX;
        vector<int> dp(n + 1, INT_MAX);
        deque<int> dq;
        dq.push_back(0);
        dp[0] = 0;
        for(int i = 1; i <= n; i++) {
            while(dq.size() && 2 * dq.front() < i - 1)
                dq.pop_front();
            dp[i] = dp[dq.front()] + prices[i - 1];
            while(dq.size() && dp[i] <= dp[dq.back()])
                dq.pop_back();
            dq.push_back(i);
            if(i + i >= n) res = min(res, dp[i]);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}