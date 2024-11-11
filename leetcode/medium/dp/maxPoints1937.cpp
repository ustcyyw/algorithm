/**
 * @Time : 2022/12/15-9:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        int n = points.size(), m = points[0].size();
        vector<vector<long long>>dp(n + 1, vector(m, 0ll));
        for(int i = 1; i <= n; i++){
            long long val = -1;
            for(int j = 0; j < m; j++){
                val = max(val - 1, dp[i - 1][j]);
                dp[i][j] = val;
            }
            val = -1;
            for(int j = m - 1; j >= 0; j--){
                val = max(val - 1, dp[i - 1][j]);
                dp[i][j] = max(dp[i][j], val) + points[i - 1][j];
            }
        }
        long long res = -1;
        for(int j = 0; j < m; j++)
            res = max(res, dp[n][j]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}