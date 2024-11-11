/**
 * @Time : 2022/11/2-8:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
    int dy[8] = {1, -1, 0, 1, -1, 0, 1, -1};
    int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
        if (grid[0][0]) return -1;
        int n = grid.size(), step = 0;
        if (n == 1) return 1;
        queue<vector<int>> queue;
        queue.push({0, 0});
        grid[0][0] = 1;
        while (!queue.empty()) {
            step++;
            int sz = queue.size();
            for (int i = 0; i < sz; i++) {
                vector<int> cur = queue.front();
                queue.pop();
                int x = cur[0], y = cur[1];
                for (int k = 0; k < 8; k++) {
                    int nx = x + dx[k], ny = y + dy[k];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= n || grid[nx][ny] == 1) continue;
                    if (nx == n - 1 && ny == n - 1) return step + 1;
                    grid[nx][ny] = 1;
                    queue.push({nx, ny});
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}