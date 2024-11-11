/**
 * @Time : 2022/12/15-10:55 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个由 0 和 1 组成的矩阵 matrix ，找出只包含 1 的最大矩形，并返回其面积。

注意：此题 matrix 输入格式为一维 01 字符串数组。

 

示例 1：



输入：matrix = ["10100","10111","11111","10010"]
输出：6
解释：最大矩形如上图所示。
示例 2：

输入：matrix = []
输出：0
示例 3：

输入：matrix = ["0"]
输出：0
示例 4：

输入：matrix = ["1"]
输出：1
示例 5：

输入：matrix = ["00"]
输出：0
 

提示：

rows == matrix.length
cols == matrix[0].length
0 <= row, cols <= 200
matrix[i][j] 为 '0' 或 '1'

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/PLYXKQ

注意：本题与主站 85 题相同（输入参数格式不同）： https://algorithm-cn.com/problems/maximal-rectangle/
 */
class Solution {
public:
    int maximalRectangle(vector<string>& matrix) {
        if(matrix.size() == 0) return 0;
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> rowLen(n, vector(m, 0));
        for(int i = 0; i < n; i++){
            for(int j = m - 1, l = 0; j >= 0; j--){
                l = matrix[i][j] == '1' ? l + 1 : 0;
                rowLen[i][j] = l;
            }
        }
        int res = 0;
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int l = INT_MAX;
                for(int k = i; k < n && rowLen[k][j] > 0; k++){
                    l = min(l, rowLen[k][j]);
                    res = max(res, (k - i + 1) * l);
                }
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<string> arr = {"10100","10111","11111","10010"};
    s.maximalRectangle(arr);
    cout << 0 << endl;
}