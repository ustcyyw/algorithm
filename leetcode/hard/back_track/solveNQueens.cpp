/**
 * @Time : 2022/5/14-11:34 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<bool> col, up, down;
    vector<vector<string>> res;
    int n;
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        col = vector(n, false);
        up = vector(2 * n - 1, false), down = vector(2 * n - 1, false);
        vector<vector<char>> grid = vector(n, vector(n, '.'));
        // 每一行都必须排一个元素，因此不需要按行枚举，每次回溯都是对该行枚举
        for(int j = 0; j < n; j++)
            backTrack(grid, 0, j);
        return res;
    }
    void backTrack(vector<vector<char>>& grid, int x, int y){
        col[y] = true, up[x + y] = true, down[x - y + n - 1] = true;
        grid[x][y] = 'Q';
        if(x + 1 == n) addOne(grid);
        for(int j = 0; j < n && x + 1 < n; j++){
            if(!col[j] && !up[x + 1 + j] && !down[x + 1 - j + n - 1])
                backTrack(grid, x + 1, j);
        }
        col[y] = false, up[x + y] = false, down[x - y + n - 1] = false;
        grid[x][y] = '.';
    }
    void addOne(vector<vector<char>>& grid){
        vector<string> cur_solve;
        for(int i = 0; i < n; i++)
            cur_solve.push_back(string(grid[i].begin(), grid[i].end()));
        res.push_back(cur_solve);
    }
};

int main(){

}