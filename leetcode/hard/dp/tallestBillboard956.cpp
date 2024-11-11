/**
 * @Time : 2023/3/1-12:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 你正在安装一个广告牌，并希望它高度最大。这块广告牌将有两个钢制支架，两边各一个。每个钢支架的高度必须相等。

你有一堆可以焊接在一起的钢筋 rods。举个例子，如果钢筋的长度为 1、2 和 3，则可以将它们焊接在一起形成长度为 6 的支架。

返回 广告牌的最大可能安装高度 。如果没法安装广告牌，请返回 0 。

 

示例 1：

输入：[1,2,3,6]
输出：6
解释：我们有两个不相交的子集 {1,2,3} 和 {6}，它们具有相同的和 sum = 6。
示例 2：

输入：[1,2,3,4,5,6]
输出：10
解释：我们有两个不相交的子集 {2,3,5} 和 {4,6}，它们具有相同的和 sum = 10。
示例 3：

输入：[1,2]
输出：0
解释：没法安装广告牌，所以返回 0。
 

提示：

0 <= rods.length <= 20
1 <= rods[i] <= 1000
sum(rods[i]) <= 5000

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/tallest-billboard
 */
class Solution {
public:
    /*
     * 选取的总和为偶数，左右各一半
     * 如果记左边长度为负，右边长度为正，那么满足题意的情况就是选取总和为0
     * 对于每一个元素num，就有3种可能，放左边、放右边、不选
     * 分别对应对总长度的贡献 -num、+num、0
     *
     * dp[i][j]: 截止第i个元素，总和为j的最大高度
     * 这里最大高度就是右边的长度
     * 总和可能为负，但是所有元素的和为sum，那么总和最大为sum，最小为-sum
     * 那么j的范围可以通过平移修改为 0,sum * 2 + 1
     *
     * dp[i][j] = max{dp[i - 1][j + num], dp[i - 1][j], dp[i - 1][j - num] + num}
     * 分别对应：i-1处总和为j + num，当前数放左边；i-1处总和为j，当前不选；i-1处总和为j - num，当前数放右边
     *
     * 选取总和 这个维度做状态变量的切入点
     * 提示中特别说明了 sum(rods[i]) <= 5000 状态有限
     */
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size(), sum = accumulate(rods.begin(), rods.end(), 0), m = 2 * sum;
        vector<vector<int>> dp(n, vector(m + 1, -1));
        dp[0][sum] = 0, dp[0][0] = 0, dp[0][sum + rods[0]] = rods[0];
        for(int i = 1; i < n; i++){
            int num = rods[i];
            for(int j = 0; j <= m; j++){
                int t1 = j + num <= m ? dp[i - 1][j + num] : -1;
                int t2 = j - num >= 0 && dp[i - 1][j - num] != -1 ? dp[i - 1][j - num] + num : -1;
                dp[i][j] = max({t1, dp[i - 1][j], t2});
            }
        }
        return dp[n - 1][sum];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}