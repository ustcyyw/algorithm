/**
 * @Time : 2022/8/19-10:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个 n x n 整数矩阵 arr ，请你返回 非零偏移下降路径 数字和的最小值。

非零偏移下降路径 定义为：从 arr 数组中的每一行选择一个数字，且按顺序选出来的数字中，相邻数字不在原数组的同一列。

 

示例 1：



输入：arr = [[1,2,3],[4,5,6],[7,8,9]]
输出：13
解释：
所有非零偏移下降路径包括：
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
下降路径中数字和最小的是 [1,5,7] ，所以答案是 13 。
示例 2：

输入：grid = [[7]]
输出：7
 

提示：

n == grid.length == grid[i].length
1 <= n <= 200
-99 <= grid[i][j] <= 99

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-falling-path-sum-ii
 */
class Solution {
public:
    /**
     * 执行用时：32 ms, 在所有 C++ 提交中击败了68.61%的用户
     * 内存消耗：14.2 MB, 在所有 C++ 提交中击败了75.55%的用户
     *
     * 总是应该选择上一行的最小路径，然后这一行选一个元素接上去
     * 但是要求相邻两行不能同列（因此还要记录列序号），就需要上一行的最小路径和次小路径
     * 因为二者只可能有一条和当前行某元素的列序号相同
     * 从最小和次小路径中优先使用最小，就可以得到以当前元素结尾的最小路径
     */
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        if(n == 1) return grid[0][0];
        vector<pair<int, int>> firsts, seconds; // 上一层路径最小值的索引及最小值
        firsts.push_back(make_pair(-1,0)), seconds.push_back(make_pair(-1,0));
        for(int i = 0; i < n; i++){
            pair<int, int> f = firsts[i], s = seconds[i];
            int i1 = -1, p1 = 20000, i2 = -1, p2 = 20000;
            for(int j = 0; j < n; j++){
                int cur_p = (f.first == j ? s.second : f.second) + grid[i][j];
                if(cur_p <= p1) {
                    p2 = p1, i2 = i1;
                    p1 = cur_p, i1 = j;
                } else if(cur_p < p2){
                    p2 = cur_p, i2 = j;
                }
            }
            firsts.push_back(make_pair(i1, p1)), seconds.push_back(make_pair(i2, p2));
        }
        pair<int, int> f = firsts[n], s = seconds[n];
        return min(f.second, s.second);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}