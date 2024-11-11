/**
 * @Time : 2022/12/13-10:30 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
    const int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
public:
    int n, m;
    vector<int> id, size;
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        n = grid.size(), m = grid[0].size();
        for(int i = 0; i < n * m; i++){
            id.push_back(i);
            size.push_back(1);
        }
        vector<vector<int>> infos, q_infos;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                infos.push_back({i, j, grid[i][j]});
        }
        for(int i = 0; i < queries.size(); i++)
            q_infos.push_back({i, queries[i]});
        sort(q_infos.begin(), q_infos.end(),
             [](auto& a, auto& b) -> bool {return a[1] < b[1];});
        sort(infos.begin(), infos.end(),
             [](auto& a, auto& b) -> bool {return a[2] < b[2];});
        vector<int> ans(queries.size(), 0);
        for(int i = 0, j = 0; i < queries.size(); i++){
            int query = q_infos[i][1], index = q_infos[i][0];
            if(query <= grid[0][0])continue;
            while (j < infos.size() && infos[j][2] < query) {
                merge(grid, infos[j][0], infos[j][1], query);
                j++;
            }
            ans[index] = size[find(0)];
        }
        return ans;
    }

    void merge(vector<vector<int>>& grid, int x, int y, int t){
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] >= t) continue;
            connect(x * m + y, nx * m + ny);
        }
    }

    void connect(int p, int q){
        p = find(p), q = find(q);
        if(p != q){
            id[q] = p;
            size[p] += size[q];
        }
    }

    int find(int p){
        if(id[p] == p) return p;
        id[p] = find(id[p]);
        return id[p];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}