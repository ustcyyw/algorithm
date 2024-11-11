/**
 * @Time : 2022/8/3-5:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个二维整数数组 grid ，大小为 m x n，其中每个单元格都含一个正整数。

转角路径 定义为：包含至多一个弯的一组相邻单元。具体而言，路径应该完全 向水平方向 或者 向竖直方向 移动过弯（如果存在弯），而不能访问之前访问过的单元格。在过弯之后，路径应当完全朝 另一个 方向行进：如果之前是向水平方向，那么就应该变为向竖直方向；反之亦然。当然，同样不能访问之前已经访问过的单元格。

一条路径的 乘积 定义为：路径上所有值的乘积。

请你从 grid 中找出一条乘积中尾随零数目最多的转角路径，并返回该路径中尾随零的数目。

注意：

水平 移动是指向左或右移动。
竖直 移动是指向上或下移动。
 

示例 1：



输入：grid = [[23,17,15,3,20],[8,1,20,27,11],[9,4,6,2,21],[40,9,1,10,6],[22,7,4,5,3]]
输出：3
解释：左侧的图展示了一条有效的转角路径。
其乘积为 15 * 20 * 6 * 1 * 10 = 18000 ，共计 3 个尾随零。
可以证明在这条转角路径的乘积中尾随零数目最多。

中间的图不是一条有效的转角路径，因为它有不止一个弯。
右侧的图也不是一条有效的转角路径，因为它需要重复访问已经访问过的单元格。
示例 2：



输入：grid = [[4,3,2],[7,6,1],[8,8,8]]
输出：0
解释：网格如上图所示。
不存在乘积含尾随零的转角路径。
 

提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 105
1 <= m * n <= 105
1 <= grid[i][j] <= 1000


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-trailing-zeros-in-a-cornered-path
 */
class Solution {
public:
    int m, n;
    int maxTrailingZeros(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        vector<vector<int>> two = vector(m, vector(n, 0)), five = vector(m, vector(n, 0));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int num = grid[i][j];
                two[i][j] = count_factor(num, 2);
                five[i][j] = count_factor(num, 5);
            }
        }
        vector<vector<int>> row_two = row_sum(two), col_two = col_sum(two);
        vector<vector<int>> row_five = row_sum(five), col_five = col_sum(five);
        int res = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                vector<int> info2 = count_pos(row_two, col_two, i, j);
                vector<int> info5 = count_pos(row_five, col_five, i, j);
                int t1 = min(info2[0] + info2[2], info5[0] + info5[2]);
                int t2 = min(info2[0] + info2[3], info5[0] + info5[3]);
                int t3 = min(info2[1] + info2[2], info5[1] + info5[2]);
                int t4 = min(info2[1] + info2[3], info5[1] + info5[3]);
                res = max(res, max(max(t1, t2), max(t3, t4)));
                cout << i << ',' << j << " : " << max(max(t1, t2), max(t3, t4)) << endl;
            }
        }
        return res;
    }

    vector<int> count_pos(vector<vector<int>>& row, vector<vector<int>>& col, int i, int j){
        vector<int> res;
        res.push_back(row[i][j]); // left
        res.push_back(row[i][n] - row[i][j + 1]); // right
        res.push_back(col[j][i + 1]); // up
        res.push_back(col[j][m] - col[j][i]); // down
        return res;
    }

    vector<vector<int>> row_sum(vector<vector<int>>& grid){
        vector<vector<int>> res = vector(m, vector(n + 1, 0));
        for(int i = 0; i < m; i++){
            for(int j = 1; j <= n; j++)
                res[i][j] = res[i][j - 1] + grid[i][j - 1];
        }
        return res;
    }

    vector<vector<int>> col_sum(vector<vector<int>>& grid){
        vector<vector<int>> res = vector(n, vector(m + 1, 0));
        for(int i = 0; i < n; i++){
            for(int j = 1; j <= m; j++)
                res[i][j] = res[i][j - 1] + grid[j - 1][i];
        }
        return res;
    }

    int count_factor(int num, int p){
        int count = 0;
        while (num % p == 0){
            count++;
            num /= p;
        }
        return count;
    }
};

int main(){
    Solution s;
    vector<vector<int>> arr = {{23,17,15,3,20},{8,1,20,27,11},{9,4,6,2,21},{40,9,1,10,6},{22,7,4,5,3}};
    s.maxTrailingZeros(arr);
    cout << 0 << endl;
}