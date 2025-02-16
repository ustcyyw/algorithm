#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5, P = 13331;
int dx[4] = {-1,-1,1,1}, dy[4] = {-1,1,1,-1};

class Solution {
public:
    int n, m;
    vector<vector<int>> grid;
    vector<vector<vector<int>>> dp, hasOne;
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        this->grid = grid;
        this->n = grid.size(), this->m = grid[0].size();
        dp = vector(n, vector(m, vector(4, -1)));
        hasOne = vector(n, vector(m, vector(4, -1)));
        bool flag = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1) flag = 1;
                for(int k = 0; k < 4; k++)
                    dfs(i, j, k);
            }
        }
        if(flag == 0) return 0; // 没有开头点的情况
        int ans = 1; // 有开头点 那么至少开头点长度就是1了
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1) continue;
                for(int k1 = 0; k1 < 4; k1++) {
                    if(!hasOne[i][j][k1]) continue;
                    if(k1 == 0) ans = max(dp[i][j][k1] + dp[i][j][3], ans);
                    else ans = max(dp[i][j][k1] + dp[i][j][k1 - 1], ans);
                }
            }
        }
        return ans;
    }

    void dfs(int x, int y, int k) {
        if(grid[x][y] == 1) {
            dp[x][y][k] = 0, hasOne[x][y][k] = 1;
            return;
        }
        if(dp[x][y][k] != -1) return;
        int nx = x + dx[k], ny = y + dy[k];
        if(nx < 0 || ny < 0 || nx == n || ny == m || grid[x][y] == grid[nx][ny]) {
            dp[x][y][k] = 1, hasOne[x][y][k] = 0;
            return;
        }
        dfs(nx, ny, k);
        dp[x][y][k] = dp[nx][ny][k] + 1;
        hasOne[x][y][k] = hasOne[nx][ny][k];
        if(grid[nx][ny] == 1) {
            hasOne[x][y][k] = grid[x][y] == 2;
        }
    }
};

int main() {
    vector<int> arr1 = {8,10,9};
    vector<int> arr2 = {10,6,6};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa","ac"};
    vector<vector<int>> arr4 = {{1,2,2,2,2},{2,2,2,2,0},{2,0,0,0,0},{0,0,2,2,2},{2,0,0,2,0}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
    s.lenOfVDiagonal(arr4);
}
