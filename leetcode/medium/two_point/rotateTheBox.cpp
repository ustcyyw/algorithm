/**
 * @Time : 2022/7/26-7:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个 m x n 的字符矩阵 box ，它表示一个箱子的侧视图。箱子的每一个格子可能为：

'#' 表示石头
'*' 表示固定的障碍物
'.' 表示空位置
这个箱子被 顺时针旋转 90 度 ，由于重力原因，部分石头的位置会发生改变。每个石头会垂直掉落，直到它遇到障碍物，另一个石头或者箱子的底部。重力 不会 影响障碍物的位置，同时箱子旋转不会产生惯性 ，也就是说石头的水平位置不会发生改变。

题目保证初始时 box 中的石头要么在一个障碍物上，要么在另一个石头上，要么在箱子的底部。

请你返回一个 n x m的矩阵，表示按照上述旋转后，箱子内的结果。

 

示例 1：



输入：box = [["#",".","#"]]
输出：[["."],
      ["#"],
      ["#"]]
示例 2：



输入：box = [["#",".","*","."],
            ["#","#","*","."]]
输出：[["#","."],
      ["#","#"],
      ["*","*"],
      [".","."]]
示例 3：



输入：box = [["#","#","*",".","*","."],
            ["#","#","#","*",".","."],
            ["#","#","#",".","#","."]]
输出：[[".","#","#"],
      [".","#","#"],
      ["#","#","*"],
      ["#","*","."],
      ["#",".","*"],
      ["#",".","."]]
 

提示：

m == box.length
n == box[i].length
1 <= m, n <= 500
box[i][j] 只可能是 '#' ，'*' 或者 '.' 。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/rotating-the-box
 */
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int n = box.size(), m = box[0].size();
        vector<vector<char>> res = vector(m, vector(n, '.'));
        for(int i = 0; i < n; i++){ // 处理原box的每行
            for(int j = m - 1, bottom = m - 1; j >= 0; j--){
                char c = box[i][j];
                if(c == '.') continue;
                if(c == '*') {
                    res[j][n - i - 1] = '*';
                    bottom = j - 1;
                } else res[bottom--][n - i - 1] = '#';
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<vector<char>> arr = {{'#','.','#'}};
    s.rotateTheBox(arr);
    cout << 0 << endl;
}