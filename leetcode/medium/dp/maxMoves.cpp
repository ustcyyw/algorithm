/**
 * @Time : 2023/5/14-12:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int dx[3] = {-1, 0, 1};
class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), res = 0;
        vector<vector<int>> dp(n, vector(m, 0));
        for(int j = 1; j < m; j++) {
            for(int i = 0; i < n; i++) {
                for(int k = 0; k < 3; k++) {
                    int x = i + dx[k], y = j - 1;
                    // dp[x][y] || y == 0 这个条件 限制了只能从第一列出发
                    if(x >= 0 && x < n && grid[i][j] > grid[x][y] && (dp[x][y] || y == 0))
                        dp[i][j] = max(dp[x][y] + 1, dp[i][j]);
                }
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}