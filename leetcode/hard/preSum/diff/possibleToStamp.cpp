/**
 * @Time : 2022/8/25-10:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m;
    bool possibleToStamp(vector<vector<int>>& grid, int height, int width) {
        n = grid.size(), m = grid[0].size();
        vector<vector<int>> info = get_sum(grid), diff = vector(n + 1, vector(m + 1, 0));
        if(height > n || width > m)
            return get_sum(info, 0, 0, n - 1, m - 1) == n * m;
        for(int i = height - 1; i < n; i++){
            for(int j = width - 1; j < m; j++){
                int x = i - height + 1, y = j - width + 1;
                if(get_sum(info, x, y, i, j) == 0){
                    diff[x][y]++, diff[i + 1][j + 1]++;
                    diff[i + 1][y]--, diff[x][j + 1]--;
                }
            }
        }
        vector<vector<int>> cover = get_sum(diff);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 0 && cover[i + 1][j + 1] == 0) return false;
            }
        }
        return true;
    }

    int get_sum(vector<vector<int>>& info, int x, int y, int i, int j){
        return info[i + 1][j + 1] - info[i + 1][y] - info[x][j + 1] + info[x][y];
    }

    vector<vector<int>> get_sum(vector<vector<int>>& grid){
        vector<vector<int>> sum = vector(n + 1, vector(m + 1, 0));
        for(int i = 1; i <= n; i++){
            for(int j = 1, line_sum = 0; j <= m; j++){
                line_sum += grid[i - 1][j - 1];
                sum[i][j] = line_sum + sum[i - 1][j];
            }
        }
        return sum;
    }
};

int main(){
    Solution s;
    vector<vector<int>> arr = {{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}};
//    s.possibleToStamp(arr, 9, 4);
    cout << s.possibleToStamp(arr, 9, 4) << endl;
}