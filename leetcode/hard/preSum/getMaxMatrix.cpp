/**
 * @Time : 2022/7/5-7:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个正整数、负整数和 0 组成的 N × M 矩阵，编写代码找出元素总和最大的子矩阵。

返回一个数组 [r1, c1, r2, c2]，其中 r1, c1 分别代表子矩阵左上角的行号和列号，r2, c2 分别代表右下角的行号和列号。若有多个满足条件的子矩阵，返回任意一个均可。

注意：本题相对书上原题稍作改动

示例：

输入：
[
   [-1,0],
   [0,-1]
]
输出：[0,1,0,1]
解释：输入中标粗的元素即为输出所表示的矩阵
 

说明：

1 <= matrix.length, matrix[0].length <= 200

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/max-submatrix-lcci
 */

class Solution {
public:
    int n, m;
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> col = get_row_sum(matrix);
        int r1, c1, r2, c2, square = -2147483648;
        for(int down = 0; down < n; down++){
            for(int up = 0; up <= down; up++){
                for(int right = 0, sum = 0, minVal = 0, left = 0; right < m; right++){
                    sum += col[right][down + 1] - col[right][up];
                    int curS = sum - minVal;
                    // 先更新面积，再更新最小前缀和，因为矩阵至少有一个元素；
                    // 先更新最小前缀和，可能就是当前这个，一减就导致矩阵是空的
                    if(curS > square){
                        square = curS;
                        r1 = up, r2 = down, c1 = left, c2 = right;
                    }
                    if(minVal > sum){
                        minVal = sum;
                        // 最小前缀和对应的下标是right，之后要排除的元素是[0,right]，因此最大矩阵的左边界是right + 1
                        left = right + 1;
                    }
                }
            }
        }
        return {r1, c1, r2, c2};
    }
    // col[i][j] 表示第i列[0,i]个元素的前缀和
    vector<vector<int>> get_row_sum(vector<vector<int>>& matrix){
        vector<vector<int>> col = vector(m, vector(n + 1, 0));
        for(int i = 0; i < m; i++){
            for(int j = 1; j <= n; j++)
                col[i][j] = col[i][j - 1] + matrix[j - 1][i];
        }
        return col;
    }
};

int main(){
    Solution s;
    vector<vector<int>> matrix = {{-1,0},{0,-1}};
    s.getMaxMatrix(matrix);
    cout << 0 << endl;
}