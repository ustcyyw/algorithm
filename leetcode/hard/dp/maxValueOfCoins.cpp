/**
 * @Time : 2022/7/12-10:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * dp[i][j] 表示截止第i个钱包，共拿j个硬币获得的最大金钱
     * dp[0][j]一定为0，第0个钱包，无法获得任何钱；dp[i][0]一定为0，最多拿0个硬币，无法获得任何钱
     * dp[i][j] = max{dp[i - 1][j - t] + sum[i][t]}，截止前一个钱包拿j - t个硬币，在当前拿前t个硬币
     * 其中sum[i][j]表示第i个钱包的前j个硬币一共多少钱，在sum中i，j的都从1开始取
     *
     * 并且要保证获得金钱最多，一定要拿取k个硬币
     * 硬币总数为m，截止到当前栈一共有pre_m个硬币, 其后还有after_m个硬币可以拿
     * after_m = m - pre_m
     * 截止当前栈能拿到的硬币最多为 min(k, pre_m)
     * 截止当前栈应该拿的硬币最少为max(0, k - after_m)
     * k-after_m表示，要拿满k个硬币，后续所有硬币都拿走，截止目前也需要拿k - after_m多个
     * 注意题目保证了k < m,一定可以拿满k个
     */
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        int n = piles.size(), m = 0; // m 表示硬币总数
        vector<vector<int>> sum = vector(n + 1, vector(1, 0));
        for(int i = 0; i < n; i++){
            vector<int>& pile = piles[i];
            for(int j = 0, temp = 0; j < pile.size(); j++){
                temp += pile[j];
                sum[i + 1].push_back(temp);
            }
            m += pile.size();
        }
        vector<vector<int>> dp = vector(n + 1, vector(k + 1, 0));
        for(int i = 1, pre_m = 0; i <= n; i++){
            pre_m += piles[i - 1].size();
            int after_m = m - pre_m;
            for(int j = max(0, k - after_m); j <= min(k, pre_m); j++){
                // t表示当前栈要拿多少个硬币，可以不拿，t从0开始；
                // 最多拿piles[i - 1].size()个并且不能超过截止当前栈一共要拿的硬币数j
                for(int t = 0; t <= piles[i - 1].size() && t <= j; t++)
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - t] + sum[i][t]);
            }
        }
        return dp[n][k];
    }
};

int main(){
    Solution s;
    vector<vector<int>> piles = {{100},{100},{100},{100},{100},{100},{1,1,1,1,1,1,700}};
    s.maxValueOfCoins(piles, 7);
    cout << 0 << endl;
}