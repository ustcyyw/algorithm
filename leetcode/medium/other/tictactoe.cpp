/**
 * @Time : 2022/6/19-9:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 设计一个算法，判断玩家是否赢了井字游戏。输入是一个 N x N 的数组棋盘，由字符" "，"X"和"O"组成，其中字符" "代表一个空位。

以下是井字游戏的规则：

玩家轮流将字符放入空位（" "）中。
第一个玩家总是放字符"O"，且第二个玩家总是放字符"X"。
"X"和"O"只允许放置在空位中，不允许对已放有字符的位置进行填充。
当有N个相同（且非空）的字符填充任何行、列或对角线时，游戏结束，对应该字符的玩家获胜。
当所有位置非空时，也算为游戏结束。
如果游戏结束，玩家不允许再放置字符。
如果游戏存在获胜者，就返回该游戏的获胜者使用的字符（"X"或"O"）；如果游戏以平局结束，则返回 "Draw"；如果仍会有行动（游戏未结束），则返回 "Pending"。

示例 1：

输入： board = ["O X"," XO","X O"]
输出： "X"
示例 2：

输入： board = ["OOX","XXO","OXO"]
输出： "Draw"
解释： 没有玩家获胜且不存在空位
示例 3：

输入： board = ["OOX","XXO","OX "]
输出： "Pending"
解释： 没有玩家获胜且仍存在空位
提示：

1 <= board.length == board[i].length <= 100
输入一定遵循井字棋规则


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/tic-tac-toe-lcci
 */
class Solution {
public:
    /**
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：7.9 MB, 在所有 C++ 提交中击败了51.58%的用户
     */
    string tictactoe(vector<string>& board) {
        int n = board.size(), filled = 0;
        vector<int> countX = vector(2 * n + 2, 0), countO = vector(2 * n + 2, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(board[i][j] == ' ') continue;
                filled++;
                if(board[i][j] == 'O'){
                    if(add(n, i, j, countO)) return "0";
                }
                else if(add(n, i, j, countX))
                        return "X";
            }
        }
        for(int i = 0; i < 2 * n + 2; i++){
            if(countX[i] == n) return "X";
            if(countO[i] == n) return "O";
        }
        return filled == n * n ?  "Draw" : "Pending";
    }

    bool add(int n, int i, int j, vector<int>& count){
        count[i]++, count[j + n]++;
        if(i == j) count[n + n]++;
        if(i + j + 1 == n) count[n + n + 1]++;
        return count[i] == n || count[j + n] == n || count[n + n] == n || count[n + n + 1] == n;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}