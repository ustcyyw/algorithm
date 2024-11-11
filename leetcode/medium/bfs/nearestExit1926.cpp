/**
 * @Time : 2023/4/20-11:12 AM
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
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int n = maze.size(), m = maze[0].size(), step = 0;
        maze[entrance[0]][entrance[1]] = '+';
        queue<vector<int>> queue;
        queue.push(entrance);
        while (!queue.empty()){
            int sz = queue.size();
            for(int k = 0; k < sz; k++) {
                vector<int>& pos = queue.front();
                int x = pos[0], y = pos[1];
                for(int i = 0; i < 4; i++){
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m || maze[nx][ny] == '+') continue;
                    if(nx == 0 || ny == 0 || nx == n - 1 || ny == m - 1) return step;
                    maze[nx][ny] = '+';
                    queue.push({nx, ny});
                }
                queue.pop();
            }
            step++;
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}