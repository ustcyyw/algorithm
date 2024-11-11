/**
 * @Time : 2022/8/18-7:15 PM
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
    int dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0};
    int mx[4] = {0,0,-1,1}, my[4] = {-1,1,0,0};
    int minPushBox(vector<vector<char>>& grid) {
        n = grid.size(), m = grid[0].size();
        queue<vector<int>> queue;
        vector<int> start;
        start.resize(4);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == 'B')
                    start[0] = i, start[1] = j;
                if(grid[i][j] == 'S')
                    start[2] = i, start[3] = j;
            }
        }
        int step = 0;
        unordered_set<int> marked;
        marked.insert(get_state(start[0], start[1], start[2], start[3]));
        queue.push(start);
        while (!queue.empty()){
            step++;
            int size = queue.size();
            for(int k = 0; k < size; k++){
                vector<vector<bool>> canReach = vector(n, vector(m, false));
                auto cur = queue.front();
                queue.pop();
                int bx = cur[0], by = cur[1], px = cur[2], py = cur[3];
                grid[bx][by] = 'B';
                reach(grid, canReach, px, py);
                for(int i = 0; i < 4; i++){
                    int ax = bx + dx[i], ay = by + dy[i]; // ax,ay人站的位置
                    if(!checkIn(ax, ay) || !canReach[ax][ay]) continue;
                    int ex = bx + mx[i], ey = by + my[i]; // 箱子要被推到到位置
                    if(!checkIn(ex, ey) || grid[ex][ey] == '#') continue;
                    if(grid[ex][ey] == 'T') return step;
                    int s = get_state(ex, ey, bx, by);
                    if(marked.count(s)) continue;
                    marked.insert(s);
                    queue.push({ex, ey, bx, by});
                }
                grid[bx][by] = '.';
            }
        }
        return -1;
    }

    int get_state(int a, int b, int c, int d){
        return a * 1e6 + b * 1e4 + c * 1e2 + d;
    }

    bool checkIn(int x, int y){
        return x >= 0 && y >= 0 && x < n && y < m;
    }

    void reach(vector<vector<char>>& grid, vector<vector<bool>>& canReach, int x, int y){
        canReach[x][y] = true;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(!checkIn(nx, ny)) continue;
            if(canReach[nx][ny] || grid[nx][ny] == 'B' || grid[nx][ny] == '#') continue;
            reach(grid, canReach, nx, ny);
        }
    }
};

int main(){
    Solution s;
    vector<vector<char>> grid = {{'#','#','#','#','#','#'},
                                 {'#','T','#','#','#','#'},
                                 {'#','.','.','B','.','#'},
                                 {'#','.','#','#','.','#'},
                                 {'#','.','.','.','S','#'},
                                 {'#','#','#','#','#','#'}};
    s.minPushBox(grid);
    cout << 0 << endl;
}