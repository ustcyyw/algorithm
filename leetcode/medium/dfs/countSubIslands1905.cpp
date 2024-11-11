/**
 * @Time : 2022/12/29-2:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
    const int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
public:
    int n, m;
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        n = grid1.size(), m = grid1[0].size();
        for(int id = 2, i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                if(grid1[i][j] == 1) make_id(grid1, i, j, id++);
        }
        int cnt = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                if(grid2[i][j] == 1 && grid1[i][j] > 1)
                    cnt += check(grid1, grid2, i, j, grid1[i][j]);
        }
        return cnt;
    }

    bool check(vector<vector<int>>& base, vector<vector<int>>& grid, int x, int y, int id){
        grid[x][y] = -1;
        bool flag = base[x][y] == id;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] != 1) continue;
            flag &= check(base, grid, nx, ny, id);
        }
        return flag;
    }

    void make_id(vector<vector<int>>& grid1, int x, int y, int id){
        grid1[x][y] = id;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m || grid1[nx][ny] != 1) continue;
            make_id(grid1, nx, ny, id);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}