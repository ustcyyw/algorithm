/**
 * @Time : 2023/5/2-1:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
class Solution {
public:
    int findMaxFish(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), ans = 0;
        function<int(int,int)> dfs = [&](int x, int y) -> int {
            int cnt = grid[x][y];
            grid[x][y] = 0;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if(grid[nx][ny] == 0) continue;
                cnt += dfs(nx, ny);
            }
            return cnt;
        };
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] > 0)
                    ans = max(ans, dfs(i, j));
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}