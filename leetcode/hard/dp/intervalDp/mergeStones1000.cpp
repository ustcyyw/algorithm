/**
 * @Time : 2023/11/16-8:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int max_val = 1e9;
class Solution {
public:
    /*
     * dp[i][j][m]: 区间[i,j]上合成m堆石头的最小cost
     * 转移方程
     * 1.dp[i][j][1] = dp[i][j][k] + sum[i, j]
     * 将k堆石头合成1堆 其花费需要sum[i, j]
     * 得计算出 dp[i][j][k] 后才能计算dp[i][j][1]
     * 2.dp[i][j][m] = min{dp[i][p][1] + d[p+1][j][m-1]}
     * 枚举分界点，区间[i,p]上是一堆，区间[p+1,j]上是剩下m-1堆
     * 这个划分并未有石头合成 因此没有额外消耗 就只是两部分之和
     * 注意：左边不管区间长度是多少 都让他只划分为1堆 因为左边区间2堆、3堆的情况
     * 其实就是枚举过的另外一个分割点q 满足q < p 时将[i,q]分为一堆 [q+1,p]分为1堆、2堆的情况
     * 因此左边就时分为1堆 也能将所有情况枚举到
     *
     * 边界条件 dp[i][i][1] = 0：初始的一堆石头 不需要合成
     *
     * 计算方向
     * 1. 区间dp的常规做法 枚举区间长度 从短到长
     * 2. 枚举区间的左端点，然后根据长度算右端点
     * 3. 如果要枚举分割点p，计算状态m时，得需要知道m-1的状态 因此应该先计算m这个维度
     * 4. 最后才是p的维度 枚举p的时候要注意 每次合并减少k-1堆石头 左边区间有 p - i + 1堆石头
     *  要合并成1堆 说明 p - i + 1 减少了t次（k-1）后还剩1堆 也就是 p - i + 1 - t * (k-1) = 1
     *  p = t * (k - 1) + i。p从i开始枚举，间隔就是k - 1
     */
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if(k > 2 && n % (k - 1) != 1) return -1;
        vector<int> sum(n + 1, 0);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + stones[i - 1];
        vector<vector<vector<int>>> dp(n, vector(n, vector(k + 1, max_val)));
        for(int i = 0; i < n; i++)
            dp[i][i][1] = 0;
        for(int len = 2; len <= n; len++) {
            for(int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                for(int m = 2; m <= min(k, len); m++) {
                    for(int p = i; p + 1 <= j; p += k - 1)
                        dp[i][j][m] = min(dp[i][j][m], dp[i][p][1] + dp[p + 1][j][m - 1]);
                }
                dp[i][j][1] = dp[i][j][k] + sum[j + 1] - sum[i];
            }
        }
        return dp[0][n - 1][1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}