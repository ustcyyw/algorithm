/**
 * @Time : 2023/8/8-9:56 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 401, dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
int ids[N * N];
class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size(), target = n * n - 1;
        if(n == 1) return 0;
        queue<vector<int>> queue;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                if(grid[i][j] == 1) queue.push({i, j});
        }
        vector<vector<vector<int>>> points(2 * n + 5);
        int step = 2;
        while (!queue.empty()) {
            int sz = queue.size();
            for(int i = 0; i < sz; i++) {
                vector<int>& pos = queue.front();
                points[step - 1].push_back(pos);
                int x = pos[0], y = pos[1];
                for(int j = 0; j < 4; j++) {
                    int nx = x + dx[j], ny = y + dy[j];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n || grid[nx][ny] != 0) continue;
                    grid[nx][ny] = step;
                    queue.push({nx, ny});
                }
                queue.pop();
            }
            step++;
        }
        for(int i = 0; i < n * n; i++)
            ids[i] = i;
        while (true) {
            for(vector<int>& pos : points[step]) {
                int x = pos[0], y = pos[1];
                for(int j = 0; j < 4; j++) {
                    int nx = x + dx[j], ny = y + dy[j];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n || grid[nx][ny] < step) continue;
                    connect(x * n + y, nx * n + ny);
                }
            }
            if(find(0) == find(target)) break;
            step--;
        }
        return step - 1;
    }

    int find(int p){
        if(ids[p] == p) return p;
        return ids[p] = find(ids[p]);
    }

    void connect(int p, int q) {
        ids[find(p)] = find(q);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}