/**
 * @Time : 2022/9/19-10:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/**
 * 公司计划面试 2n 人。给你一个数组 costs ，其中 costs[i] = [aCosti, bCosti] 。第 i 人飞往 a 市的费用为 aCosti ，飞往 b 市的费用为 bCosti 。

返回将每个人都飞到 a 、b 中某座城市的最低费用，要求每个城市都有 n 人抵达。

 

示例 1：

输入：costs = [[10,20],[30,200],[400,50],[30,20]]
输出：110
解释：
第一个人去 a 市，费用为 10。
第二个人去 a 市，费用为 30。
第三个人去 b 市，费用为 50。
第四个人去 b 市，费用为 20。

最低总费用为 10 + 30 + 50 + 20 = 110，每个城市都有一半的人在面试。
示例 2：

输入：costs = [[259,770],[448,54],[926,667],[184,139],[840,118],[577,469]]
输出：1859
示例 3：

输入：costs = [[515,563],[451,713],[537,709],[343,819],[855,779],[457,60],[650,359],[631,42]]
输出：3086
 

提示：

2 * n == costs.length
2 <= costs.length <= 100
costs.length 为偶数
1 <= aCosti, bCosti <= 1000

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/two-city-scheduling
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * dp[i][j]表示分配[0,i]上的人，并且有j个被分配到a城市的最小花费
     * dp[i][j] = min(dp[i - 1][j] + costs[i][1], dp[i - 1][j - 1] + costs[i][0])
     * 其中 0 <= j <= i, 并且根据题目要求，最终要对半分，也就是说j > n的状态没有任何计算意义
     *
     * 边界条件dp[0][0] = 0,不对任何人分配时，花费为0
     */
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int n = costs.size(), m = n / 2;
        vector<vector<int>> dp(n + 1, vector(m + 1, (int)1e7));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            dp[i][0] = dp[i - 1][0] + costs[i - 1][1];
            if(i <= m)
                dp[i][i] = dp[i - 1][i - 1] + costs[i - 1][0];
            for(int j = 1; j < min(m + 1, i); j++)
                dp[i][j] = min(dp[i - 1][j] + costs[i - 1][1], dp[i - 1][j - 1] + costs[i - 1][0]);
        }
        return dp[n][m];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}