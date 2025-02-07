/**
 * @Time : 2022/8/20-11:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 在一个小城市里，有 m 个房子排成一排，你需要给每个房子涂上 n 种颜色之一（颜色编号为 1 到 n ）。有的房子去年夏天已经涂过颜色了，所以这些房子不可以被重新涂色。

我们将连续相同颜色尽可能多的房子称为一个街区。（比方说 houses = [1,2,2,3,3,2,1,1] ，它包含 5 个街区  [{1}, {2,2}, {3,3}, {2}, {1,1}] 。）

给你一个数组 houses ，一个 m * n 的矩阵 cost 和一个整数 target ，其中：

houses[i]：是第 i 个房子的颜色，0 表示这个房子还没有被涂色。
cost[i][j]：是将第 i 个房子涂成颜色 j+1 的花费。
请你返回房子涂色方案的最小总花费，使得每个房子都被涂色后，恰好组成 target 个街区。如果没有可用的涂色方案，请返回 -1 。

 

示例 1：

输入：houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
输出：9
解释：房子涂色方案为 [1,2,2,1,1]
此方案包含 target = 3 个街区，分别是 [{1}, {2,2}, {1,1}]。
涂色的总花费为 (1 + 1 + 1 + 1 + 5) = 9。
示例 2：

输入：houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
输出：11
解释：有的房子已经被涂色了，在此基础上涂色方案为 [2,2,1,2,2]
此方案包含 target = 3 个街区，分别是 [{2,2}, {1}, {2,2}]。
给第一个和最后一个房子涂色的花费为 (10 + 1) = 11。
示例 3：

输入：houses = [0,0,0,0,0], cost = [[1,10],[10,1],[1,10],[10,1],[1,10]], m = 5, n = 2, target = 5
输出：5
示例 4：

输入：houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3
输出：-1
解释：房子已经被涂色并组成了 4 个街区，分别是 [{3},{1},{2},{3}] ，无法形成 target = 3 个街区。
 

提示：

m == houses.length == cost.length
n == cost[i].length
1 <= m <= 100
1 <= n <= 20
1 <= target <= m
0 <= houses[i] <= n
1 <= cost[i][j] <= 10^4


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/paint-house-iii
 */
class Solution {
public:
    /**
     * dp[i][j][k]:在houses[0,i]内的房子一共有j个街区（色块），且以颜色k为结尾的最小cost
     *
     * 有两种涂色方式，一种是与上一个房子涂成相同的颜色 dp[i][j][k] = dp[i-1][j][k] + cost[i][k - 1]
     * 一种是与上一个房子涂成不同的颜色 dp[i][j][k] = min(dp[i-1][j-1][l], l != k) + cost[i][k - 1]
     * 注意有些house的颜色已经固定了，是不能更改的
     *
     * 执行用时：160 ms, 在所有 C++ 提交中击败了30.92%的用户
     * 内存消耗：18.8 MB, 在所有 C++ 提交中击败了7.24%的用户
     */
    int max_val = 1e7;
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        vector<vector<vector<int>>> dp = vector(m, vector(target + 1, vector(n + 1, max_val)));
        if(houses[0] != 0)
            dp[0][1][houses[0]] = 0; // 已经涂色过，成本为0
        else {
            for(int k = 1; k <= n; k++)
                dp[0][1][k] = cost[0][k - 1];
        }
        for(int i = 1; i < m; i++){
            for(int j = 1; j <= target; j++){
                if(j > i + 1) break; // 街区的数量比房子还多，不可能出现，直接跳过计算
                if(houses[i] != 0) // 当前房子的颜色已被确定的情况，不用枚举当前的颜色
                    fixed_color(dp, cost, n, i, j, houses[i]);
                else { // 当前房子的颜色自己选的情况
                    for (int color = 1; color <= n; color++) { // 枚举当前房子可能的颜色
                        fixed_color(dp, cost, n, i, j, color);
                        if(dp[i][j][color] != max_val) // 没涂色的还要加上当前的涂色成本
                            dp[i][j][color] += cost[i][color - 1];
                    }
                }

            }
        }
        int res = max_val;
        for(int k = 1; k <= n; k++)
            res = min(res, dp[m - 1][target][k]);
        return res == max_val ? -1 : res;
    }
    // 计算指定房子，指定街区数时，该房子涂色的最小成本（但未加上当前房子涂色的花费）
    void fixed_color(vector<vector<vector<int>>>& dp, vector<vector<int>>& cost,
        int n, int i, int j, int color){
        dp[i][j][color] = dp[i - 1][j][color]; // 与前面同色的情况
        for(int k = 1; k <= n; k++){ // 与前面不同色的情况
            if(k != color)
                dp[i][j][color] = min(dp[i][j][color], dp[i - 1][j - 1][k]);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}