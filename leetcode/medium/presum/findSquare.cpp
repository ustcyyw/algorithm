/**
 * @Time : 2022/7/5-9:03 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个方阵，其中每个单元(像素)非黑即白。设计一个算法，找出 4 条边皆为黑色像素的最大子方阵。

返回一个数组 [r, c, size] ，其中 r, c 分别代表子方阵左上角的行号和列号，size 是子方阵的边长。若有多个满足条件的子方阵，返回 r 最小的，若 r 相同，返回 c 最小的子方阵。若无满足条件的子方阵，返回空数组。

示例 1:

输入:
[
   [1,0,1],
   [0,0,1],
   [0,0,1]
]
输出: [1,0,2]
解释: 输入中 0 代表黑色，1 代表白色，标粗的元素即为满足条件的最大子方阵
示例 2:

输入:
[
   [0,1,1],
   [1,0,1],
   [1,1,0]
]
输出: [0,0,1]
提示：

matrix.length == matrix[0].length <= 200

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/max-black-square-lcci
 */
class Solution {
public:
    /**
     * 前缀和预处理边长信息
     */
    int n;
    vector<int> findSquare(vector<vector<int>>& matrix) {
        n = matrix.size();
        vector<vector<int>> rowLen = get_row_length(matrix), colLen = get_col_length(matrix);
        int len = 0, r, c;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == 1) continue;
                for(int l = min(rowLen[i][j], colLen[j][i]); l > len ;l--){
                    if(rowLen[i - l + 1][j] >= l && colLen[j - l + 1][i] >= l){
                        len = l;
                        r = i, c = j;
                    }
                }
            }
        }
        if(len == 0) return {};
        return {r, c, len};
    }
    // 指定元素(行，列)左侧0的个数，如果某个0左边没有更多0，其值设置为1
    vector<vector<int>> get_row_length(vector<vector<int>>& matrix){
        vector<vector<int>> res = vector(n, vector(n, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0, len = 0; j < n; j++){
                len = matrix[i][j] == 0 ? len + 1 : 0;
                res[i][j] = len;
            }
        }
        return res;
    }
    // 指定元素(列，行)上方0的个数，如果某个0上方没有更多0，其值设置为1
    vector<vector<int>> get_col_length(vector<vector<int>>& matrix){
        vector<vector<int>> res = vector(n, vector(n, 0));
        for(int j = 0; j < n; j++){
            for(int i = 0, len = 0; i < n; i++){
                len = matrix[i][j] == 0 ? len + 1 : 0;
                res[j][i] = len;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<vector<int>> matrix = {{0,0,0},{0,1,0},{0,0,0}};
    s.findSquare(matrix);
    cout << 0 << endl;
}