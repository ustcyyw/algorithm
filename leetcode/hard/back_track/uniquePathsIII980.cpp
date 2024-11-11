/**
 * @Time : 2022/12/14-9:44 PM
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
    int n, m, zero;
    int uniquePathsIII(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        int x, y;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == 0) zero++;
                if(grid[i][j] == 1) x = i, y = j;
            }
        }
        vector<vector<bool>> marked(n, vector(m, false));
        return backTrack(grid, marked, x, y, 0);
    }

    int backTrack(vector<vector<int>>& grid, vector<vector<bool>>& marked, int x, int y, int cnt){
        if(grid[x][y] == 2) return cnt == zero;
        if(grid[x][y] == 0) cnt++;
        marked[x][y] = true;
        int res = 0;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m || marked[nx][ny] || grid[nx][ny] == -1) continue;
            res += backTrack(grid, marked, nx, ny, cnt);
        }
        marked[x][y] = false;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}