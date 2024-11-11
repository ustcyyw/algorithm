/**
 * @Time : 2023/4/20-11:11 AM
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
     * 动态规划 dp[i][j]表示第i分钟到达j结点的最小花费
     * 显然时间维度i从小到大计算
     * 而结点维度，只有通过边才能从一个结点到另外一个结点，因此结点维度枚举边来进行转移
     */
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& fees) {
        int n = fees.size(), res = INT_MAX;
        vector<vector<int>> dp(maxTime + 1, vector(n, (int)1e9));
        dp[0][0] = fees[0];
        for(int t = 1; t <= maxTime; t++){
            for(auto& edge : edges) {
                int v = edge[0], w = edge[1], time = edge[2];
                if(t - time < 0) continue;
                // 从w在t - time时刻出发，经过time的时间到达v
                dp[t][v] = min(dp[t][v], dp[t - time][w] + fees[v]);
                dp[t][w] = min(dp[t][w], dp[t - time][v] + fees[w]);
            }
        }
        for(int t = 0; t <= maxTime; t++)
            res = min(res, dp[t][n - 1]);
        return res >= 1e9 ? -1 : res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}