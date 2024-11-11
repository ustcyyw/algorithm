/**
 * @Time : 2023/3/2-12:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
class Solution {
public:
    /*
     * bfs的运用题，只要想起来 bfs求不同状态之间的最短路径即可
     * 状态的理解：可以是坐标 + 其它，本题的其它就是获得的钥匙的情况
     * 由于钥匙最多6把，可以用状态压缩的方式去表示。
     *
     * 简单一些的题里面，坐标或者结点编号就定义了状态，<其它>就没有了
     */
    int shortestPathAllKeys(vector<string>& grid) {
        int n = grid.size(), m = grid[0].size(), k = 0, sx, sy;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                char c = grid[i][j];
                if(c >= 'a' && c <= 'f') k++;
                if(c == '@') sx = i, sy = j;
            }
        }
        int full = (1 << k) - 1, step = 1;
        vector<vector<vector<bool>>> marked(n, vector(m, vector(full + 1, false)));
        marked[sx][sy][0] = true;
        queue<vector<int>> queue;
        queue.push({sx, sy, 0});
        while (!queue.empty()){
            int sz = queue.size();
            for(int j = 0; j < sz; j++){
                vector<int>& infos = queue.front();
                int x = infos[0], y = infos[1], status = infos[2];
                for(int i = 0; i < 4; i++){
                    int nx = x + dx[i], ny = y + dy[i];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == '#') continue;
                    char c = grid[nx][ny];
                    if(c >= 'A' && c <= 'F' && !((1 << (c - 'A')) & status)) continue;
                    int ns = c >= 'a' && c <= 'f' ? status | (1 << (c - 'a')): status;
                    if(ns == full) return step;
                    if(marked[nx][ny][ns]) continue;
                    marked[nx][ny][ns] = true;
                    queue.push({nx, ny, ns});
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