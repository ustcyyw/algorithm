/**
 * @Time : 2022/8/18-9:43 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 在一个 8x8 的棋盘上，放置着若干「黑皇后」和一个「白国王」。

给定一个由整数坐标组成的数组 queens ，表示黑皇后的位置；以及一对坐标 king ，表示白国王的位置，返回所有可以攻击国王的皇后的坐标(任意顺序)。

 

示例 1：



输入：queens = [[0,1],[1,0],[4,0],[0,4],[3,3],[2,4]], king = [0,0]
输出：[[0,1],[1,0],[3,3]]
解释：
[0,1] 的皇后可以攻击到国王，因为他们在同一行上。
[1,0] 的皇后可以攻击到国王，因为他们在同一列上。
[3,3] 的皇后可以攻击到国王，因为他们在同一条对角线上。
[0,4] 的皇后无法攻击到国王，因为她被位于 [0,1] 的皇后挡住了。
[4,0] 的皇后无法攻击到国王，因为她被位于 [1,0] 的皇后挡住了。
[2,4] 的皇后无法攻击到国王，因为她和国王不在同一行/列/对角线上。
示例 2：



输入：queens = [[0,0],[1,1],[2,2],[3,4],[3,5],[4,4],[4,5]], king = [3,3]
输出：[[2,2],[3,4],[4,4]]
示例 3：



输入：queens = [[5,6],[7,7],[2,1],[0,7],[1,6],[5,1],[3,7],[0,3],[4,0],[1,2],[6,3],[5,0],[0,4],[2,2],[1,1],[6,4],[5,4],[0,0],[2,6],[4,5],[5,2],[1,4],[7,5],[2,3],[0,5],[4,2],[1,0],[2,7],[0,1],[4,6],[6,1],[0,6],[4,3],[1,7]], king = [3,4]
输出：[[2,3],[1,4],[1,6],[3,7],[4,3],[5,4],[4,5]]
 

提示：

1 <= queens.length <= 63
queens[i].length == 2
0 <= queens[i][j] < 8
king.length == 2
0 <= king[0], king[1] < 8
一个棋盘格上最多只能放置一枚棋子。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/queens-that-can-attack-the-king
 */
class Solution {
public:
    /**
     * 执行用时：4 ms, 在所有 C++ 提交中击败了85.63%的用户
     * 内存消耗：10.4 MB, 在所有 C++ 提交中击败了93.13%的用户
     */
    int dx[8] = {0,0,1,1,1,-1,-1,-1};
    int dy[8] = {-1,1,1,-1,0,0,1,-1};
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        vector<vector<int>> res, grid = vector(8, vector(8, 0));
        for(auto& queen : queens)
            grid[queen[0]][queen[1]] = 1;
        for(int k = 0; k < 8; k++){
            int x = dx[k], y = dy[k];
            for(int i = king[0], j = king[1]; check(i, j); i += x, j += y){
                if(grid[i][j] == 1){
                    res.push_back({i, j});
                    break;
                }
            }
        }
        return res;
    }

    bool check(int x, int y){
        return x >= 0 && y >= 0 && x < 8 && y < 8;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}