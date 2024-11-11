/**
 * @Time : 2023/9/27-2:54 PM
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
     * dp[i][s]: 截止第一组中的结点i，第二组结点被连接的状态为s的最小花费
     * 要求i接第二组上的一个或者多个结点，不能不接
     * dp[i][s]的转移:
     * 1.当前状态是dp[i][s]，但是i可以连接多个第二组的结点，i连接j后 状态由s变为 s | (1 << i)
     * 花费为 dp[i][s] + cost[i][j]
     * 2.前置状态是dp[i-1][s],i连接j后 状态由s变为 s | (1 << i)
     * 花费为 dp[i - 1][s] + cost[i][j]
     */
    int connectTwoGroups(vector<vector<int>>& cost) {
        int n = cost.size(), m = cost[0].size(), u = (1 << m) - 1;
        vector<vector<int>> dp(n + 1, vector(u + 1, (int)1e9));
        dp[0][0] = 0; // 两个组没有任何结点连接的成本为0
        for(int i = 1; i <= n; i++) {
            for(int s = 0; s <= u; s++) { // 这里枚举集合 不能忘了0 对于i=1的结点，前置对group2的连接状态是0
                for(int j = 0; j < m; j++) {
                    // 枚举i连接的第二组的结点j，注意i可以连接多个j
                    // 转移项中的dp[i][s] + cost[i][j]可能就是i连接了多个第二组的结点后再考虑还要不要连接j
                    int t = 1 << j;
                    dp[i][s | t] = min({dp[i][s | t], dp[i][s] + cost[i - 1][j],
                                        dp[i - 1][s] + cost[i - 1][j]});
                }
            }
        }
        return dp[n][u];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}