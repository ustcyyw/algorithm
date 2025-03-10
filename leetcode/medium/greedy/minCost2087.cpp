/**
 * @Time : 2022/8/28-12:34 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个 m x n 的网格图，其中 (0, 0) 是最左上角的格子，(m - 1, n - 1) 是最右下角的格子。给你一个整数数组 startPos ，startPos = [startrow, startcol] 表示 初始 有一个 机器人 在格子 (startrow, startcol) 处。同时给你一个整数数组 homePos ，homePos = [homerow, homecol] 表示机器人的 家 在格子 (homerow, homecol) 处。

机器人需要回家。每一步它可以往四个方向移动：上，下，左，右，同时机器人不能移出边界。每一步移动都有一定代价。再给你两个下标从 0 开始的额整数数组：长度为 m 的数组 rowCosts  和长度为 n 的数组 colCosts 。

如果机器人往 上 或者往 下 移动到第 r 行 的格子，那么代价为 rowCosts[r] 。
如果机器人往 左 或者往 右 移动到第 c 列 的格子，那么代价为 colCosts[c] 。
请你返回机器人回家需要的 最小总代价 。

 

示例 1：



输入：startPos = [1, 0], homePos = [2, 3], rowCosts = [5, 4, 3], colCosts = [8, 2, 6, 7]
输出：18
解释：一个最优路径为：
从 (1, 0) 开始
-> 往下走到 (2, 0) 。代价为 rowCosts[2] = 3 。
-> 往右走到 (2, 1) 。代价为 colCosts[1] = 2 。
-> 往右走到 (2, 2) 。代价为 colCosts[2] = 6 。
-> 往右走到 (2, 3) 。代价为 colCosts[3] = 7 。
总代价为 3 + 2 + 6 + 7 = 18
示例 2：

输入：startPos = [0, 0], homePos = [0, 0], rowCosts = [5], colCosts = [26]
输出：0
解释：机器人已经在家了，所以不需要移动。总代价为 0 。
 

提示：

m == rowCosts.length
n == colCosts.length
1 <= m, n <= 105
0 <= rowCosts[r], colCosts[c] <= 104
startPos.length == 2
homePos.length == 2
0 <= startrow, homerow < m
0 <= startcol, homecol < n


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-cost-homecoming-of-a-robot-in-a-grid
 */
class Solution {
public:
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        int res = 0;
        for(int i = min(startPos[0], homePos[0]); i <= max(startPos[0], homePos[0]); i++)
            res += rowCosts[i];
        for(int i = min(startPos[1], homePos[1]); i <= max(startPos[1], homePos[1]); i++)
            res += colCosts[i];
        return res - rowCosts[startPos[0]] - colCosts[startPos[1]]
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}