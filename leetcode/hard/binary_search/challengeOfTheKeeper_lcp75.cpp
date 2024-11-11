/**
 * @Time : 2023/4/23-9:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
const int N = 200 * 200 + 5;
class Solution {
public:
    int n;
    vector<string> grid;
    vector<vector<int>> steps;
    int challengeOfTheKeeper(vector<string>& maze) {
        n = maze.size();
        grid = maze;
        int sx = 0, sy = 0, ex = 0, ey = 0;
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(grid[i][j] == 'S')
                    sx = i, sy = j;
                if(grid[i][j] == 'T')
                    ex = i, ey = j;
            }
        }
        steps = bfs(ex, ey);
        int lo = 0, hi = N;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if(check(sx, sy, mid, ex, ey)) hi = mid;
            else lo = mid + 1;
        }
        return lo == N ? -1 : lo;
    }
    // 二分 到达终点能接受的最大负面距离 如果小于等于该负面距离，就认为该点可以走，看最终能否到达终点
    bool check(int a, int b, int val, int tx, int ty) {
        vector<vector<bool>> marked(n, vector(n, false));
        marked[a][b] = true;
        queue<vector<int>> queue;
        queue.push({a, b});
        while (!queue.empty()) {
            vector<int>& cur = queue.front();
            int x = cur[0], y = cur[1];
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                if (marked[nx][ny] || grid[nx][ny] == '#') continue;
                if(nx == tx && ny == ty) return true;
                marked[nx][ny] = true;
                if(lengthLess(nx, ny, val))
                    queue.push({nx, ny});
            }
            queue.pop();
        }
        return false;
    }
    // 判断经过该点被转换后，负面距离是否小于val
    bool lengthLess(int x, int y, int val){
        if(grid[x][y] != '.') return false;
        int nx = n - x - 1, ny = n - y - 1; // 镜像坐标
        return (grid[x][ny] == '#' || steps[x][ny] <= val) &&
               (grid[nx][y] == '#' || steps[nx][y] <= val);
    }
    // 计算各个点到终点的最短距离
    vector<vector<int>> bfs(int a, int b) {
        steps = vector(n, vector(n, INT_MAX));
        vector<vector<bool>> marked(n, vector(n, false));
        marked[a][b] = true;
        int step = 0;
        queue<vector<int>> queue;
        queue.push({a, b});
        while (!queue.empty()) {
            int sz = queue.size();
            for(int k = 0; k < sz; k++){
                vector<int>& cur = queue.front();
                int x = cur[0], y = cur[1];
                steps[x][y] = step;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                    if(grid[nx][ny] == '#' || marked[nx][ny]) continue;
                    marked[nx][ny] = true;
                    queue.push({nx, ny});
                }
                queue.pop();
            }
            step++;
        }
        return steps;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}