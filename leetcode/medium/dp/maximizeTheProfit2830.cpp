/**
 * @Time : 2023/9/5-11:27 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximizeTheProfit(int n, vector<vector<int>>& offers) {
        sort(offers.begin(), offers.end(), [](auto& a, auto& b) -> bool {return a[1] < b[1];});
        int m = offers.size();
        vector<int> dp(m, 0);
        dp[0] = offers[0][2];
        for(int i = 1; i < m; i++) {
            int lo = -1, hi = i - 1, s = offers[i][0];
            while (lo < hi) {
                int mid = (lo + hi + 1) >> 1;
                if(offers[mid][1] >= s) hi = mid - 1;
                else lo = mid;
            }
            if(lo == -1) dp[i] = max(dp[i - 1], offers[i][2]);
            else dp[i] = max(dp[i - 1], offers[i][2] + dp[lo]);
        }
        return dp[m - 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}