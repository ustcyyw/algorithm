/**
 * @Time : 2022/7/31-12:48 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 1是守卫，2是墙，3是被守护的，0是没被守护的
     *
     * 执行用时：424 ms, 在所有 C++ 提交中击败了71.49%的用户
     * 内存消耗：150.3 MB, 在所有 C++ 提交中击败了66.09%的用户
     */
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> grid = vector(m, vector(n, 0));
        for(auto& guard : guards)
            grid[guard[0]][guard[1]] = 1;
        for(auto& wall : walls)
            grid[wall[0]][wall[1]] = 2;
        for(int i = 0; i < m; i++){
            for(int j = 0, flag = 0; j < n; j++){
                if(grid[i][j] == 1) flag = 3;
                else if(grid[i][j] == 2) flag = 0;
                else if(grid[i][j] == 0) grid[i][j] = flag;
            }
            for(int j = n - 1, flag = 0; j >= 0; j--){
                if(grid[i][j] == 1) flag = 3;
                else if(grid[i][j] == 2) flag = 0;
                else if(grid[i][j] == 0) grid[i][j] = flag;
            }
        }
        for(int j = 0; j < n; j++){
            for(int i = 0, flag = 0; i < m; i++){
                if(grid[i][j] == 1) flag = 3;
                else if(grid[i][j] == 2) flag = 0;
                else if(grid[i][j] == 0) grid[i][j] = flag;
            }
            for(int i = m - 1, flag = 0; i >= 0; i--){
                if(grid[i][j] == 1) flag = 3;
                else if(grid[i][j] == 2) flag = 0;
                else if(grid[i][j] == 0) grid[i][j] = flag;
            }
        }
        int count = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++)
                count += grid[i][j] == 0 ? 1 : 0;
        }
        return count;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}