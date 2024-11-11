/**
 * @Time : 2022/11/17-4:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
    int n;
    vector<int> id;
    int swimInWater(vector<vector<int>>& grid) {
        n = grid.size();
        if(n == 1) return 0;
        id = vector(n * n, 0);
        for(int i = 0; i < id.size(); i++)
            id[i] = i;
        vector<vector<int>> infos; // 水位及对应的坐标
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++)
                infos.push_back({grid[i][j], i, j});
        }
        sort(infos.begin(), infos.end());
        int target = key(n - 1, n - 1);
        for(auto& info : infos){
            int x = info[1], y = info[2];
            for(int i = 0; i < 4; i++){
                int nx = x + dx[i], ny = y + dy[i];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n || grid[nx][ny] > grid[x][y]) continue;
                int p = key(x, y), q = key(nx, ny);
                connect(p, q);
                if(find(target) == find(0)) return info[0];
            }
        }
        return 2500;
    }

    int key(int x, int y){
        return x * n + y;
    }

    int find(int p){
        if(id[p] == p) return p;
        id[p] = find(id[p]);
        return id[p];
    }

    void connect(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return;
        id[p] = q;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}