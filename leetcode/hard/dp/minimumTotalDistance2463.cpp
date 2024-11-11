/**
 * @Time : 2023/5/4-10:21 PM
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
     * dp[i][j]: 工厂编号[1,i]的工厂 修理前j台机器的最短距离
     */
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        int n = robot.size(), m = factory.size();
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());
        vector<int> limits(m, 0);
        limits[0] = factory[0][1];
        for(int i = 1; i < m; i++)
            limits[i] = limits[i - 1] + factory[i][1];
        vector<vector<long long>> dp(m + 1, vector(n + 1, LONG_LONG_MAX));
        for(int i = 0; i <= m; i++)
            dp[i][0] = 0;
        for(int i = 1; i <= m; i++){
            int x = factory[i - 1][0], cnt = factory[i - 1][1];
            for(int j = 1; j <= min(limits[i - 1], n); j++){
                dp[i][j] = dp[i - 1][j]; // i工厂一台机器人都不修
                long long dis = 0;
                for(int k = 1; k <= min(cnt, j); k++) { // 枚举第i个工厂修理的机器数
                    dis += abs(x - robot[j - k]);
                    if(dp[i - 1][j - k] != LONG_LONG_MAX)
                        dp[i][j] = min(dp[i][j], dis + dp[i - 1][j - k]);
                }
            }
        }
        return dp[m][n];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}