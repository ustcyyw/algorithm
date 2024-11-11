/**
 * @Time : 2024/5/13-10:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<ll>> dp(n, vector(m, LONG_LONG_MIN));
        vector<vector<ll>> row(n, vector(m, 0ll)), col(m, vector(n, 0ll));
        ll ans = LONG_LONG_MIN;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int num = grid[i][j];
                if(i > 0 && col[j][i - 1] + num > dp[i][j]) {
                    dp[i][j] = col[j][i - 1] + num;
                    ans = max(ans, dp[i][j]);
                }
                if(j > 0 && row[i][j - 1] + num > dp[i][j]) {
                    dp[i][j] = row[i][j - 1] + num;
                    ans = max(ans, dp[i][j]);
                }
                dp[i][j] = max(0ll, dp[i][j]);
                if(i > 0) col[j][i] = max(col[j][i - 1], dp[i][j] - num);
                else col[j][i] = dp[i][j] - num;
                if(j > 0) row[i][j] = max(row[i][j - 1], dp[i][j] - num);
                else row[i][j] = dp[i][j] - num;
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}