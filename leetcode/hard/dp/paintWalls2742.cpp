/**
 * @Time : 2023/7/18-10:54 AM
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
     * dp[i][j] 截止到第i个墙，第一个人的(工作时长+刷墙)至少为j的最小花费
     * 第一个人的(工作时长+刷墙)就是2个人总的可以刷的墙数
     *
     * 一定有：dp[i][j] = min(dp[i][j + 1], dp[i - 1][j])
     * 意义为：截止第i个墙，两个人至少刷j个墙的最小花费
     * 1.小于等于两个人至少刷j+1个墙的花费
     * 2.小于等于截止i-1个墙，两个人至少刷j个墙的最小花费
     *
     * if(t >= j) dp[i][j] = min(dp[i][j], c)
     * 第一个人刷当前墙（i这个墙）就能完成超过j个墙，那么截止第i个墙，至少刷j个墙的最小花费还可能就是c
     * 否则
     * dp[i][j] = min(dp[i][j], dp[i - 1][j - t] + c);
     * dp[i - 1][j - t] + c：截止i-1这个墙至少刷j - t个墙的最小花费，再加上第i个墙可以贡献t个墙，但花费要再+c
     */
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        vector<vector<int>> dp(n + 1, vector(n + 2, INT_MAX));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++) {
            int c = cost[i - 1], t = time[i - 1] + 1;
            for(int j = n; j > 0; j--) {
                dp[i][j] = min(dp[i][j + 1], dp[i - 1][j]);
                if(t >= j) dp[i][j] = min(dp[i][j], c);
                else if(dp[i - 1][j - t] != INT_MAX)
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - t] + c);
            }
        }
        return dp[n][n];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}