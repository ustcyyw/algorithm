/**
 * @Time : 2022/8/19-9:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 这里有一幅服务器分布图，服务器的位置标识在 m * n 的整数矩阵网格 grid 中，1 表示单元格上有服务器，0 表示没有。

如果两台服务器位于同一行或者同一列，我们就认为它们之间可以进行通信。

请你统计并返回能够与至少一台其他服务器进行通信的服务器的数量。

 

示例 1：



输入：grid = [[1,0],[0,1]]
输出：0
解释：没有一台服务器能与其他服务器进行通信。
示例 2：



输入：grid = [[1,0],[1,1]]
输出：3
解释：所有这些服务器都至少可以与一台别的服务器进行通信。
示例 3：



输入：grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
输出：4
解释：第一行的两台服务器互相通信，第三列的两台服务器互相通信，但右下角的服务器无法与其他服务器通信。
 

提示：

m == grid.length
n == grid[i].length
1 <= m <= 250
1 <= n <= 250
grid[i][j] == 0 or 1

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/count-servers-that-communicate
 */
class Solution {
public:
    /**
     * 执行用时：48 ms, 在所有 C++ 提交中击败了65.60%的用户
     * 内存消耗：21.8 MB, 在所有 C++ 提交中击败了45.04%的用户
     */
    int countServers(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), total = 0;
        vector<int> row = vector(n, -1), col = vector(m, 0);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == 1){
                    col[j]++, total++;
                    if(row[i] == -1) row[i] = j; // -1表示这一行还没记录，此时这行记录该元素的列值
                    else if(row[i] >= 0) row[i] = -2; // 该行已经记录过列值列，又出现一个，设置为-2表示已经出现过至少2次
                }
            }
        }
        for(int i = 0; i < n; i++){
            if(row[i] >= 0 && col[row[i]] == 1)
                total--;
        }
        return total;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}